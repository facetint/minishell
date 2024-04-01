/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcoskun <hcoskun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:34:07 by facetint          #+#    #+#             */
/*   Updated: 2024/03/31 17:04:16 by hcoskun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "../../includes/minishell.h"
#include "../../includes/env.h"
#include "../../includes/utils.h"
#include "../../memory-allocator/allocator.h"
#include <stdio.h>

void	handle_builtin(t_command *cmd, t_file_descriptors fds)
{
	execute_builtin(cmd, (int []){fds.inp_fd, fds.out_fd});
	close_fds(fds);
	if (should_run_in_child(cmd))
		exit(0);
}

void	handle_external(t_command *cmd, t_file_descriptors fds)
{
	char	*path_cmd;
	char	**envp;
	char	**args;
	char	*path;

	dup2(fds.inp_fd, STDIN_FILENO);
	dup2(fds.out_fd, STDOUT_FILENO);
	close_fds(fds);
	path_cmd = find_path(cmd->args[0]);
	path = ft_unsafe_strdup(path_cmd);
	envp = ft_unsafe_strarrdup(to_arr(*get_global_env()));
	args = ft_unsafe_strarrdup(cmd->args);
	abort_function();
	execve(path, args, envp);
	exit(127);
}

void	handle_command(t_command *cmd, int *prev_p, int *next_p)
{
	int					pid;
	int					inp_fd;
	int					out_fd;
	t_file_descriptors	fds;

	if (!cmd->args[0])
		return ;
	inp_fd = get_input_fd(prev_p, cmd);
	out_fd = get_output_fd(next_p, cmd);
	if (inp_fd < 0 || out_fd < 0)
		return ;
	fds = (t_file_descriptors){inp_fd, out_fd, prev_p, next_p};
	pid = 0;
	if (should_run_in_child(cmd))
		pid = fork();
	cmd->pid = pid;
	if (pid < 0)
		return (pid_error(prev_p, next_p));
	if (pid > 0)
		return (close_redirections(fds));
	if (fds.inp_fd < 0 || fds.out_fd < 0)
	{
		if (should_run_in_child(cmd))
			exit(1);
		*get_exit_status() = 1;
		return ;
	}
	if (isbuiltin(cmd->args[0]))
		handle_builtin(cmd, fds);
	else
		handle_external(cmd, fds);
}

void	wait_children(t_command *latest)
{
	int			exit_status;

	if (latest->pid == 0)
		return ;
	waitpid(latest->pid, &exit_status, 0);
	if (*get_exit_status() == 0)
		*get_exit_status() = exit_status >> 8;
	while (wait(NULL) > 0)
		;
}

void	execute(t_command *cur)
{
	t_command	*latest;
	int			*prev_p;
	int			*next_p;

	*get_exit_status() = 0;
	prev_p = NULL;
	next_p = NULL;
	while (cur)
	{
		close_pipe(prev_p);
		prev_p = next_p;
		if (cur->next)
		{
			next_p = safe_malloc(sizeof(int) * 2);
			pipe(next_p);
		}
		else
			next_p = NULL;
		handle_command(cur, prev_p, next_p);
		latest = cur;
		cur = cur->next;
	}
	close_pipe(prev_p);
	wait_children(latest);
}
