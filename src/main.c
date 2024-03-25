/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:18:04 by facetint          #+#    #+#             */
/*   Updated: 2024/03/25 15:01:29 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "../libft/libft.h"
#include "../includes/minishell.h"
#include "../memory-allocator/allocator.h"
#include "../includes/env.h"

void set_env(char **envp) {
	t_list *lst = to_list(envp);
	if (!lst)
		return;
	*get_global_env() = lst;
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	set_env(envp);
	unset_env("OLDPWD");
	register_post_abort_func(handle_memory_error);
	register_signal_handler();
	while (1)
	{
		signal_type = PROMPT;
		char *prompt = get_prompt();
		char *input = readline(prompt);
		safe_free(prompt);
		if (!input)
			exit(*get_exit_status() % 256);

		if (*input && ft_strcmp(input, "^C"))
		{
			add_history(input);
			handle_input(input);
		}
		free(input);
		free_memory();
	}
}
