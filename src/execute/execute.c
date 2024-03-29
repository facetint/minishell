/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:34:07 by facetint          #+#    #+#             */
/*   Updated: 2024/03/29 23:07:57 by hamza            ###   ########.fr       */
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
	int result = cmd->prev || cmd->next || !isbuiltin(cmd->args[0]);
	return (result);
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

void	handle_command(t_command *cmd, int *prev_p, int *next_p)
{
	int		pid;
	char	*path_cmd;
	int		inp_fd;
	int		out_fd;

	inp_fd = get_input_fd(prev_p, cmd);
	out_fd = get_output_fd(next_p, cmd);
	if (inp_fd == -1 || out_fd == -1)
		return ;
	pid = 0;
	if (should_run_in_child(cmd))
		pid = fork();
	if (pid < 0)
		pid_error(pid, prev_p, next_p);
	if (pid > 0)
	{
		cmd->pid = pid;
		return ;
	}
	if (isbuiltin(cmd->args[0]))
	{
		handle_builtin(cmd, (int[]){inp_fd, out_fd});
		if (should_run_in_child(cmd))
			exit(0);
		return;
	}
	dup2_and_close(inp_fd, out_fd, prev_p, next_p);
	path_cmd = find_path(cmd->args[0]);
	if (!path_cmd)
		path_error(cmd);
	execve(path_cmd, cmd->args, to_arr(*get_global_env()));
	exit(127);
}

void close_pipe(int *pipe)
{
	if (pipe)
	{
		close(pipe[0]);
		close(pipe[1]);
	}
}

void	execute(t_command *cur)
{
	t_command	*latest;
	int			exit_status;
	int			*prev_p;
	int			*next_p;

	*get_exit_status() = 0;
		
	prev_p = NULL;
	next_p = NULL;
	latest = NULL;
	while (cur)
	{
		close_pipe(prev_p);
		prev_p = next_p;
		if (cur->next)
		{
			next_p = safe_malloc(sizeof(int) * 2);
			pipe(next_p);
		}
		else if (next_p)
		{
			next_p = NULL;
		}
		handle_command(cur, prev_p, next_p);
		latest = cur;
		cur = cur->next;
	}
	close_pipe(prev_p);
	if (latest->pid == 0)
	{
		*get_exit_status() = 1;
		return ;
	}
	waitpid(latest->pid, &exit_status, 0);
	if (!*get_exit_status())
		*get_exit_status() = exit_status >> 8;
	while (wait(NULL) > 0);
}
