/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:07:09 by facetint          #+#    #+#             */
/*   Updated: 2024/03/30 17:09:42 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <errno.h>
#include <string.h>

void	pid_error(int *prev_pipe, int *next_pipe)
{
	ft_putstr_fd("minishell: fork: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
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

void	path_error(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}
