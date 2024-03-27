/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:34:07 by facetint          #+#    #+#             */
/*   Updated: 2024/03/27 13:44:35 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include "../../includes/env.h"
#include "../../memory-allocator/allocator.h"
#include "../../get_next_line/get_next_line.h"
#include <fcntl.h>
#include <errno.h>

int should_run_in_child(t_command *cmd)
{
	return cmd->prev || cmd->next || !isbuiltin(cmd->args[0]);
}

void handle_command(int input_fd, int output_fd, t_command *cmd, int *prev_pipe, int *next_pipe)
{
	int		pid;
	char	*path_cmd;

	if (input_fd == -1 || output_fd == -1)
		return;
	pid = 0;
	if (should_run_in_child(cmd))
		pid = fork();
	if (pid < 0)
		pid_error(pid, prev_pipe, next_pipe);
	if (pid > 0) {
		cmd->pid = pid;
		return;
	}
	dup2_and_close(input_fd, output_fd, prev_pipe, next_pipe);
	path_cmd = find_path(cmd->args[0]);
	if (!path_cmd)
		path_error(cmd);
	execve(path_cmd, cmd->args, to_arr(*get_global_env()));
	exit(127);
}

int	get_input_fd(int *pipe, t_command *cmd)
{
	if (cmd->input != STDIN_FILENO)
		return cmd->input;
	if (pipe == NULL)
		return STDIN_FILENO;
	return pipe[0];
}

int	get_output_fd(int *pipe, t_command *cmd)
{
	if (cmd->output != STDOUT_FILENO)
		return cmd->output;
	if (pipe == NULL)
		return STDOUT_FILENO;
	return pipe[1];
}

void	execute(t_command *cmds)
{
	t_command	*cur;
	t_command	*latest;
	int			exit_status;
	int			*before_pipe = NULL;
	int			*next_pipe = NULL;

	if (!cmds->next && isbuiltin(cmds->args[0]) && cmds->args[0])
		return (handle_builtin(cmds, (int[]){STDIN_FILENO, STDOUT_FILENO}));
	*get_exit_status() = 0;
	cur = cmds;
	latest = NULL;
	while (cur)
	{
		if (before_pipe) {
			close(before_pipe[0]);
			close(before_pipe[1]);
		}
		before_pipe = next_pipe;
		if (cur->next){
			next_pipe = safe_malloc(sizeof(int) * 2);
			pipe(next_pipe);
		} else if (next_pipe) {
			next_pipe = NULL;
		}
		handle_command(get_input_fd(before_pipe, cur), get_output_fd(next_pipe, cur), cur, before_pipe, next_pipe);
		latest = cur;
		cur = cur->next;
	}
	if (before_pipe)
	{
		close(before_pipe[0]);
		close(before_pipe[1]);
	}

	if (latest->pid == 0)
	{
		*get_exit_status() = 1;
		return;
	}
	waitpid(latest->pid, &exit_status, 0);
	if (!*get_exit_status())
		*get_exit_status() = exit_status >> 8;
	while(wait(NULL) > 0);
}
