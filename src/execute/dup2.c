/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:03:20 by facetint          #+#    #+#             */
/*   Updated: 2024/03/26 16:07:54 by facetint         ###   ########.fr       */
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

void	dup2_and_close(int input_fd, int output_fd,int *prev_pipe, int *next_pipe)
{
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
}