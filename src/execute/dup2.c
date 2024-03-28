/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:03:20 by facetint          #+#    #+#             */
/*   Updated: 2024/03/28 17:29:09 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../includes/minishell.h"

void	dup2_and_close(int inp_fd, int out_fd, int *prev_p, int *next_p)
{
	dup2(inp_fd, STDIN_FILENO);
	if (inp_fd != STDIN_FILENO)
		close(inp_fd);
	dup2(out_fd, STDOUT_FILENO);
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
