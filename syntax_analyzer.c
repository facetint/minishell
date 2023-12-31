#include "parser.h"

int is_word(t_token_type type) {
	return type == UNQUOTED_WORD ||
		   type == SINGLE_QUOTED_WORD ||
		   type == DOUBLE_QUOTED_WORD;
}

/**
 * check if the token is an operator (redirection operator or pipe)
 * @param type the token type
 * @return 1 if the token is an operator, 0 otherwise
 */
int is_operator(t_token_type type) {
	return type == HEREDOC_REDIRECTION ||
		   type == INPUT_REDIRECTION ||
		   type == OUTPUT_REDIRECTION ||
		   type == APPEND_REDIRECTION ||
		   type == PIPE;
}

int is_there_lack_of_word(t_token *lexer_data) {
	int wait_for_word;

	wait_for_word = 1;
	while (lexer_data)
	{
		if (lexer_data->type == DELIMITER)
			lexer_data = lexer_data->next;
		if (wait_for_word && !is_word(lexer_data->type))
			return 0;
		if (is_word(lexer_data->type))
			wait_for_word = 0;
		else if (is_operator(lexer_data->type))
			wait_for_word = 1;
		lexer_data = lexer_data->next;
	}
	return wait_for_word == 0;
}

int are_quotes_valid(const char *input, t_token *lexer_data) {
	/* not implemented yet */
	return 1;
}

int is_there_unknown_token(t_token *lexer_data) {
	while (lexer_data)
	{
		if (lexer_data->type == UNKNOWN)
			return 1;
		lexer_data = lexer_data->next;
	}
	return 0;
}

int is_valid(const char *input, t_token *lexer_data) {
	return !is_there_unknown_token(lexer_data)
		   && are_quotes_valid(input, lexer_data)
		   && is_there_lack_of_word(lexer_data);
}