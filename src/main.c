/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcoskun <hcoskun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:18:04 by facetint          #+#    #+#             */
/*   Updated: 2024/03/16 17:49:12 by hcoskun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include "../libft/libft.h"
#include "../includes/minishell.h"
#include "../memory-allocator/allocator.h"
#include "../includes/env.h"

void set_env(char **envp) {
	t_list *lst = to_list(envp);
	if (!lst)
		return;
	*get_global_env() = *lst;
	free(lst);
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	set_env(envp);
	signal_type = DEFAULT;
	register_post_abort_func(handle_memory_error);
	register_signal_handler();
	while (1)
	{
		char *prompt = get_prompt();
		char *input = readline(prompt);
		safe_free(prompt);
		if (!input)
			exit(EXIT_SUCCESS);
		if (*input)
		{
			handle_input(input);
			add_history(input);
		}
		free(input);
		free_memory();
	}
}
