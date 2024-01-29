#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "utils.h"
#include "libft/libft.h"
#include "minishell.h"
#include "memory-allocator/allocator.h"
#include <limits.h>

int main() {
	register_post_abort_func(handle_memory_error);
	while (1) {
		char *prompt = get_prompt();
		char *input = readline(prompt);
		safe_free(prompt);
		if (input && *input)
			handle_input(input);
		if (!input)
			printf("\n");
		free_memory();
	}
}
