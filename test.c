#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "utils.h"
#include "libft/libft.h"
#include "parser.h"

/* debug function */
char const *token_type_to_string(t_token_type type) {
	if (type == UNKNOWN)
		return "UNKNOWN";
	if (type == UNQUOTED_WORD)
		return "UNQUOTED_WORD";
	if (type == DOUBLE_QUOTED_WORD)
		return "DOUBLE_QUOTED_WORD";
	if (type == SINGLE_QUOTED_WORD)
		return "SINGLE_QUOTED_WORD";
	if (type == PIPE)
		return "PIPE";
	if (type == INPUT_REDIRECTION)
		return "INPUT_REDIRECTION";
	if (type == HEREDOC_REDIRECTION)
		return "HEREDOC_REDIRECTION";
	if (type == OUTPUT_REDIRECTION)
		return "OUTPUT_REDIRECTION";
	if (type == APPEND_REDIRECTION)
		return "APPEND_REDIRECTION";
	if (type == DELIMITER)
		return "DELIMITER";
	return "UNRECOGNIZED";
}

void unexpected_token_error(t_token *token)
{
	if (token == NULL)
		return ft_putstr_fd("syntax error occurred, null token found.\n", 2);
	ft_putstr_fd("syntax error near unexpected token '", 2);
	ft_putstr_fd((char *) token_type_to_string(token->type), 2);
	ft_putstr_fd("'\n", 2);
}

char *get_prompt() {
	char *full_path = getwd(NULL);
	char *path = get_cur_folder_name(full_path);
	char *username = getenv("USER");
	char *strings[] = {username, "@", path, "$ " };
	char *prompt = ft_str_join(strings, 4);
	free(full_path);
	return prompt;
}

int is_cmd(char *input, char *cmd)
{
	size_t len = ft_strlen(cmd);
	return is_equals_ignore_case(cmd, input, len - 1);
}

void handle_input(char *input) {
	t_token *token = lexer(input);

	expand_lexer_data(input, token);

	//debug
	if (!token) {
		printf("<No Token>\n");
		return;
	}
	while (token->next) {
		printf("\033[97m%s\033[37m(%d-%d)->", token_type_to_string(token->type), token->start, token->end);
		token = token->next;
	}
	printf("\033[97m%s\033[37m(%d-%d)\n", token_type_to_string(token->type), token->start, token->end);

	/*printf("\033[37mRedirections: %s\n", are_redirections_valid(token) ? "\033[92mVALID" : "\033[91mINVALID");
	printf("\033[37mQuotes: %s\n", are_quotes_valid(input, token) ? "\033[92mVALID" : "\033[91mINVALID");
	printf("\033[37mPipes: %s\n", are_pipes_valid(token) ? "\033[92mVALID" : "\033[91mINVALID");
	printf("\033[39m");*/
	/* test cases:
	 * ech'o' a
	 * test='o' && ech$test a
	 * test='o' && ech"$test" a
	 */
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
