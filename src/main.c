/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:18:04 by facetint          #+#    #+#             */
/*   Updated: 2024/04/02 17:34:33 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"
#include "../includes/minishell.h"
#include "../memory-allocator/allocator.h"
#include "../includes/env.h"

void	init_env(char **envp)
{
	t_list	*lst;

	lst = to_list(envp);
	if (!lst)
		return ;
	*get_env() = lst;
}

int	main(int ac, char **av, char **envp)
{
	char	*prompt;
	char	*input;

	(void)ac;
	(void)av;
	init_env(envp);
	export_env("OLDPWD=");
	register_post_abort_func(handle_memory_error);
	register_signal_handler();
	while (1)
	{
		g_signal_type = PROMPT;
		prompt = get_prompt();
		input = readline(prompt);
		safe_free(prompt);
		if (!input)
			exit(*get_exit_status() % 256);
		if (*input && ft_strcmp(input, "^C"))
		{
			add_history(input);
			handle_input(input);
		}
		free(input);
	}
}
