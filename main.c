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

t_envList *envList;

int main(int ac, char **av, char **envp) {

	envList = NULL;

	envList = make_list(envp);
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
