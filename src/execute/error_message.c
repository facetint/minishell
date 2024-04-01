/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:07:09 by facetint          #+#    #+#             */
/*   Updated: 2024/04/01 08:20:25 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include "../../includes/utils.h"
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
	print_error(cmd, "command not found");
	exit(127);
}

void	print_error(char *cmd, char *error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
}