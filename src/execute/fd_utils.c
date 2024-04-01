/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:03:20 by facetint          #+#    #+#             */
/*   Updated: 2024/04/01 07:16:56 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../includes/minishell.h"
#include <stdio.h>

void	close_redirections(t_file_descriptors fds)
{
	if (fds.inp_fd != STDIN_FILENO
		&& fds.inp_fd > 0
		&& (!fds.prev_p || fds.inp_fd != fds.prev_p[0]))
		close(fds.inp_fd);
	if (fds.out_fd != STDOUT_FILENO
		&& fds.inp_fd > 0
		&& (!fds.next_p || fds.out_fd != fds.next_p[1]))
		close(fds.out_fd);
}

void	close_fds(t_file_descriptors fds)
{
	if (fds.inp_fd != STDIN_FILENO)
		close(fds.inp_fd);
	if (fds.out_fd != STDOUT_FILENO)
		close(fds.out_fd);
	if (fds.prev_p)
	{
		if (fds.inp_fd != fds.prev_p[0])
			close(fds.prev_p[0]);
		close(fds.prev_p[1]);
	}
	if (fds.next_p)
	{
		close(fds.next_p[0]);
		if (fds.out_fd != fds.next_p[1])
			close(fds.next_p[1]);
	}
}

int	get_input_fd(int *pipe, t_command *cmd)
{
	if (cmd->input != STDIN_FILENO)
		return (cmd->input);
	if (pipe)
		return (pipe[0]);
	return (STDIN_FILENO);
}

int	get_output_fd(int *pipe, t_command *cmd)
{
	if (cmd->output != STDOUT_FILENO)
		return (cmd->output);
	if (pipe)
		return (pipe[1]);
	return (STDOUT_FILENO);
}

void	close_pipe(int *pipe)
{
	if (pipe)
	{
		close(pipe[0]);
		close(pipe[1]);
	}
}
