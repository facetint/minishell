/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:18:04 by facetint          #+#    #+#             */
/*   Updated: 2024/03/03 13:18:05 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include "includes/utils.h"
#include "libft/libft.h"
#include "includes/minishell.h"
#include "memory-allocator/allocator.h"
#include "includes/env.h"

int main(int ac, char **av, char **envp) {

	*get_global_env() = *make_list(envp);
	while (*envp)
		printf("%s\n", *envp),
		envp++;
	(void)ac;
	(void)av;

	register_post_abort_func(handle_memory_error);
	while (1) {
		char *prompt = get_prompt();
		char *input = readline(prompt);
		safe_free(prompt);
		if (input && *input)
		{
			handle_input(input);
			add_history(input);
		}
		if (!input)
			printf("\n");
		free_memory();
	}
}
