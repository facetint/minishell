/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:34:07 by facetint          #+#    #+#             */
/*   Updated: 2024/03/30 04:36:48 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "../../includes/minishell.h"
#include "../../includes/env.h"
#include "../../memory-allocator/allocator.h"
#include <stdio.h>

int	should_run_in_child(t_command *cmd)
{
	return (cmd->prev || cmd->next || !isbuiltin(cmd->args[0]));
}

int	get_input_fd(int *pipe, t_command *cmd)
{
	if (cmd->input != STDIN_FILENO)
		return (cmd->input);
	if (pipe == NULL)
		return (STDIN_FILENO);
	return (pipe[0]);
}

int	get_output_fd(int *pipe, t_command *cmd)
{
	if (cmd->output != STDOUT_FILENO)
		return (cmd->output);
	if (pipe == NULL)
		return (STDOUT_FILENO);
	return (pipe[1]);
}

void	handle_builtin(t_command *cmd, int inp_fd, int out_fd)
{
	execute_builtin(cmd, (int[]){inp_fd, out_fd});
	if (should_run_in_child(cmd))
		exit(0);
}

void	handle_external(t_command *cmd)
{
	char	*path_cmd;
	
	path_cmd = find_path(cmd->args[0]);
	if (!path_cmd)
		path_error(cmd); //todo exit?
	execve(path_cmd, cmd->args, to_arr(*get_global_env()));
	exit(127);
}

void	handle_command(t_command *cmd, int *prev_p, int *next_p)
{
	int		pid;
	int		inp_fd;
	int		out_fd;

	inp_fd = get_input_fd(prev_p, cmd);
	out_fd = get_output_fd(next_p, cmd);
	printf("%s -> inp_fd: %d out_fd: %d\n", cmd->args[0], inp_fd, out_fd);
	if (inp_fd < 0 || out_fd < 0)
		return ;
	pid = 0;
	if (should_run_in_child(cmd))
		pid = fork();
	if (pid < 0)
		return pid_error(pid, prev_p, next_p);
	cmd->pid = pid;
	if (pid > 0)
	{
		if (inp_fd != STDIN_FILENO && inp_fd != prev_p[0])
			close(inp_fd);
		if (out_fd != STDOUT_FILENO && out_fd != next_p[1])
			close(out_fd);
		return ;
	}
	if (isbuiltin(cmd->args[0]))
		handle_builtin(cmd, inp_fd, out_fd);
	else
	{
		dup2(inp_fd, STDIN_FILENO);
		dup2(out_fd, STDOUT_FILENO);
		handle_external(cmd);
	}
	close_fds(inp_fd, out_fd, prev_p, next_p);
}

void close_pipe(int *pipe)
{
	if (pipe)
	{
		close(pipe[0]);
		close(pipe[1]);
	}
}

void wait_children(t_command *latest)
{
	int			exit_status;
	
	if (latest->pid == 0)
		return ;
	waitpid(latest->pid, &exit_status, 0);
	if (!*get_exit_status())
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
			printf("pipe: [0]%d [1]%d\n", next_p[0], next_p[1]);
		}
		else if (next_p)
			next_p = NULL;
		handle_command(cur, prev_p, next_p);
		latest = cur;
		cur = cur->next;
	}
	close_pipe(prev_p);
	wait_children(latest);
}
