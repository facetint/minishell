/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:34:07 by facetint          #+#    #+#             */
/*   Updated: 2024/03/26 12:42:31 by facetint         ###   ########.fr       */
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

int should_run_in_child(t_command *cmd)
{
	return cmd->prev || cmd->next;
}

void handle_command(int input_fd, int output_fd, t_command *cmd, int *prev_pipe, int *next_pipe)
{
	int		pid;
	char	*path_cmd;

	if (input_fd == -1 || output_fd == -1)
		return;

	pid = 0;
	if (should_run_in_child(cmd))
		pid = fork(); //handle error
	if (pid < 0)
	{
		if (prev_pipe)
		{
			close(prev_pipe[0]);
			close(prev_pipe[1]);
		}
		if (next_pipe)
		{
			close(next_pipe[0]);
			close(next_pipe[1]);
		}
		exit(0);
	}	
	if (pid > 0) {
		cmd->pid = pid;
		return;
	}
	dup2(input_fd, STDIN_FILENO);
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	dup2(output_fd, STDOUT_FILENO);
	if (output_fd != STDOUT_FILENO)
		close(output_fd);
	if (prev_pipe)
	{
		if (input_fd != prev_pipe[0])
			close(prev_pipe[0]);
		close(prev_pipe[1]);
	}
	if (next_pipe)
	{
		close(next_pipe[0]);
		if (output_fd != next_pipe[1])
			close(next_pipe[1]);
	}
	path_cmd = find_path(cmd->args[0]);
	if (!path_cmd)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
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
		*get_exit_status() = 0;
		return;
	}
	waitpid(latest->pid, &exit_status, 0);
	if (!*get_exit_status())
		*get_exit_status() = exit_status >> 8;
	while(wait(NULL) > 0);
}
