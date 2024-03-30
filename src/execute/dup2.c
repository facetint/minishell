/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:03:20 by facetint          #+#    #+#             */
/*   Updated: 2024/03/30 03:49:28 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../includes/minishell.h"
#include <stdio.h>

void	close_fds(int inp_fd, int out_fd, int *prev_p, int *next_p)
{
	if (inp_fd != STDIN_FILENO)
		close(inp_fd);

	if (out_fd != STDOUT_FILENO)
		close(out_fd);
	if (prev_p)
	{
		if (inp_fd != prev_p[0])
			close(prev_p[0]);
		close(prev_p[1]);
	}
	if (next_p)
	{
		close(next_p[0]);
		if (out_fd != next_p[1])
			close(next_p[1]);
	}
}
