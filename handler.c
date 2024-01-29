#include "minishell.h"
#include "libft/libft.h"
#include <readline/readline.h>
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

# define LEXER_DEBUG
void debug(t_token *token, t_command *cmd) {
	(void) token,(void) cmd;

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
			printf("\033[97m%s\033[37m(%s)->", token_type_to_string(token->type), token->value);
		else
			printf("\033[97m%s\033[37m->", token_type_to_string(token->type));
		token = token->next;
	}
	if (is_word(token->type))
		printf("\033[97m%s\033[37m(%s)\033[97m\n", token_type_to_string(token->type), token->value);
	else
		printf("\033[97m%s\n", token_type_to_string(token->type));
#endif
}

char *read_heredoc_input(char *eof) {
	char *line = NULL;
	char *input = ft_strdup("");
	while (1) {
		line = readline("> ");
		if (!line || !*line || ft_strncmp(line, eof, INT_MAX) == 0)
			break;
		char *new = ft_str_arr_join((char *[]) {input, line, "\n"}, 3);
		safe_free(input);
		input = new;
		safe_free(line);
	}
	char *new = ft_substr(input, 0, ft_strlen(input) - 1);
	safe_free(input);
	return new;
}

void handle_heredocs(t_command *cur) {
	int i;

	while (cur) {
		i = 0;
		while (cur->redirections[i].redirected) {
			if (cur->redirections[i].flags & HEREDOC) {
				char *input = read_heredoc_input(cur->redirections[i].redirected);
				safe_free(cur->redirections[i].redirected);
				cur->redirections[i].redirected = input;
			}
			i++;
		}
		cur = cur->next;
	}
}

void handle_invalid_input(t_token *lexical_data)
{
	ft_putstr_fd("\033[91mInvalid input\n\033[39m", 2);
	uninit_tokens(lexical_data);
}

void handle_input(char *input)
{
	t_token *lexer_data;
	t_command *parser_data;

	lexer_data = lex(input);
	debug(lexer_data, NULL);
	if (!is_valid(lexer_data))
		return handle_invalid_input(lexer_data);
	expand(&lexer_data);
	unquote(lexer_data);
	parser_data = parse(lexer_data);
	handle_heredocs(parser_data);

	debug(lexer_data, parser_data);
	uninit_tokens(lexer_data);
}

void handle_memory_error(void)
{
	ft_putstr_fd("Insufficent memory! Minishell aborting...", 2);
	exit(1);
}

