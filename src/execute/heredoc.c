/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcoskun <hcoskun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:58:39 by facetint          #+#    #+#             */
/*   Updated: 2024/03/31 16:26:45 by hcoskun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <readline/readline.h>
#include "../../memory-allocator/allocator.h"

void	heredoc_to_fd(char *delimiter, int output_fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
			break ;
		if (!*line)
			line = ft_strdup("\n");
		else
			expand_string(&line);
		ft_putstr_fd(line, output_fd);
		ft_putstr_fd("\n", output_fd);
		safe_free(line);
	}
}

int	read_heredoc_input(char *delimiter)
{
	int	exit_status;
	int	pid;
	int	pipe_fd[2];

	pipe(pipe_fd);
	g_signal_type = WAITING_HEREDOC;
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		g_signal_type = IN_HEREDOC;
		heredoc_to_fd(delimiter, pipe_fd[1]);
		abort_function();
		exit(0);
	}
	else
	{
		close(pipe_fd[1]);
		waitpid(pid, &exit_status, 0);
		exit_status >>= 8;
		if (exit_status != 0)
			return (-1);
		return (pipe_fd[0]);
	}
}
