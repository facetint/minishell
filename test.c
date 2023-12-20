#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "utils.h"
#include "libft/libft.h"

char *get_prompt() {
	char *full_path = getwd(NULL);
	char *path = get_cur_folder_name(full_path);
	char *username = getenv("USER");
	char *strings[] = { username, "@", path, ">" };
	char *prompt = ft_str_join(strings, 4);
	free(full_path);
	return prompt;
}

int is_cmd(char *input, char *cmd) {
	int len = ft_strlen(cmd);
	return is_equals_ignore_case(cmd, input, len - 1);
} 

void handle_input(char *input) {
	char **parts = ft_split(input, ' ');
	char *strings[] = {"/bin/", parts[0]};
	char *cmd_path = ft_str_join(strings, 2); 
	printf("path: %s\n", cmd_path);
	char *args[] = {"-l"};
	execve(cmd_path, NULL, NULL);
}

int main() {
	do {
		char *prompt = get_prompt();
		char *input = readline(prompt);
		free(prompt);
		handle_input(input);
		free(input);
	} while (1);
}
