/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 02:37:53 by hamza             #+#    #+#             */
/*   Updated: 2024/04/02 15:52:51 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include "../includes/minishell.h"
#include <readline/readline.h>
#include <stdlib.h>

t_signal_type	g_signal_type;

void	handle_signal(int signum)
{
	(void) signum;
	*get_exit_status() = 1;
	if (g_signal_type == PROMPT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (g_signal_type == RUNNING_COMMANDS)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		*get_exit_status() = 128 + signum;
	}
	else if (g_signal_type == IN_HEREDOC)
	{
		printf("> %s  \n", rl_line_buffer);
		rl_replace_line("", 0);
		rl_on_new_line();
		exit(1);
	}
}

void	register_signal_handler(void)
{
	signal(SIGINT, handle_signal);
}
