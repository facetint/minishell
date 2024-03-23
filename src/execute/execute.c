/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcoskun <hcoskun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:34:07 by facetint          #+#    #+#             */
/*   Updated: 2024/03/23 17:23:37 by hcoskun          ###   ########.fr       */
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
#include <fcntl.h>

int should_run_in_child(t_command *cmd)
{
	return cmd->prev || cmd->next || !isbuiltin(cmd->args[0]);
}

void handle_command(int input_fd, int output_fd, t_command *cmd)
{
	int pid;
	char			*path_cmd;

	pid = 0;
	if (should_run_in_child(cmd))
		pid = fork(); //handle error
	if (pid < 0)
		return ft_putstr_fd("Fork error!", 2); //todo exit
		
	if (pid > 0) {
		cmd->pid = pid;
		return;
	}
	
	if (isbuiltin(cmd->args[0])) {
		handle_builtin(cmd, (int[]){input_fd, output_fd});
	} else {
		dup2(input_fd, STDIN_FILENO);
		dup2(output_fd, STDOUT_FILENO);

		path_cmd = find_path(cmd->args[0]);
		if (!path_cmd)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->args[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
		}
		execve(path_cmd, cmd->args, to_arr(get_global_env()));
		exit(127);
	}
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
	if (cmd->output != STDIN_FILENO)
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
			close(next_pipe[0]);
			close(next_pipe[1]);
			next_pipe = NULL;
		}

		handle_command(get_input_fd(before_pipe, cur), get_output_fd(next_pipe, cur), cur);
		
		latest = cur;
		cur = cur->next;
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
