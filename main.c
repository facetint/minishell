#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "utils.h"
#include "libft/libft.h"
#include "minishell.h"
#include "memory-allocator/allocator.h"

/* debug function */
char const *token_type_to_string(t_token_type type)
{
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
		return ft_putstr_fd("syntax error occurred, null token found.", 2);
	ft_putstr_fd("syntax error near unexpected token '", 2);
	ft_putstr_fd((char *) token_type_to_string(token->type), 2);
}

# define PARSER_DEBUG
# define LEXER_DEBUG
void debug(t_token *token, t_command *cmd) {
	(void) token;
	(void) cmd;

#ifdef PARSER_DEBUG
	if (!cmd) {
		printf("<No Command>");
		return;
	}
	while (cmd)
	{
		printf("name: %s\nargs:", *cmd->name ? cmd->name : "(empty)");
		if (cmd->args[0] == NULL)
			printf("(no args)");
		for (int i = 0; cmd->args[i]; i++)
			printf("`%s` ", cmd->args[i]);
		printf("\nredirections: ");
		if (cmd->redirections[0].redirected == NULL)
			printf("(no redirections)");
		for (int i = 0; cmd->redirections[i].redirected; i++)
			printf("`%s`(%s,%s,%s) ", cmd->redirections[i].redirected,
				   cmd->redirections[i].flags & INPUT ? "input" : "output",
				   cmd->redirections[i].flags & APPEND ? "append" : "no append",
				   cmd->redirections[i].flags & HEREDOC ? "heredoc" : "no heredoc");
		printf("\n");
		cmd = cmd->next;
	}
#endif
#ifdef LEXER_DEBUG
	if (!token) {
		printf("<No Token>\n");
		return;
	}
	while (token->next) {
		if (is_word(token->type))
			printf("\033[97m%s\033[37m(%s)[%d]->", token_type_to_string(token->type), token->value, token->end);
		else
			printf("\033[97m%s\033[37m->", token_type_to_string(token->type));
		token = token->next;
	}
	if (is_word(token->type))
		printf("\033[97m%s\033[37m(%s)[%d]\033[97m\n", token_type_to_string(token->type), token->value, token->end);
	else
		printf("\033[97m%s\n", token_type_to_string(token->type));
#endif
}

/* unprotected mallocs todo */
char *get_prompt()
{
	char *full_path = getwd(NULL);
	char *path = get_cur_folder_name(full_path);
	char *username = getenv("USER");
	char *strings[] = {username, "@", path, "$ " };
	char *prompt = ft_str_arr_join(strings, 4);
	safe_free(full_path);
	return prompt;
}

void handle_invalid_input(t_token *lexical_data)
{
	printf("\033[91mInvalid input\n\033[39m");
	uninit_tokens(lexical_data);
}

void handle_input(char *input)
{
	t_token *lexer_data;
	t_command *parser_data;

	lexer_data = lex(input);
	if (!is_valid(lexer_data))
		return handle_invalid_input(lexer_data);
	expand(&lexer_data);
	unquote(lexer_data);
	parser_data = parse(lexer_data);

	debug(lexer_data, parser_data);
	uninit_tokens(lexer_data);
}

void handle_memory_error(void)
{
	ft_putstr_fd("Insufficent memory! Minishell aborting...", 2);
	exit(1);
}

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
		safe_free(input);
		free_memory();
	}
}
