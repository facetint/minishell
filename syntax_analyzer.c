#include "parser.h"

int are_redirections_valid(t_token *lexer_data) {
	int wait_for_word;

	wait_for_word = 0;
	while (lexer_data)
	{
		if (wait_for_word && lexer_data->type != WORD)
			return 0;
		if (lexer_data->type == WORD)
			wait_for_word = 0;
		else if (lexer_data->type == HEREDOC_REDIRECTION ||
			lexer_data->type == INPUT_REDIRECTION ||
			lexer_data->type == OUTPUT_REDIRECTION ||
			lexer_data->type == APPEND_REDIRECTION) {
			wait_for_word = 1;
		}
		lexer_data = lexer_data->next;
	}
	return wait_for_word == 0;
}

int are_quotes_valid(const char *input, t_token *lexer_data) {
	while (lexer_data)
	{
		if (lexer_data->type == DOUBLE_QUOTED_ARGUMENT ||
			lexer_data->type == SINGLE_QUOTED_ARGUMENT)
		{
			if (lexer_data->start == lexer_data->end)
				return 0;
		}
		lexer_data = lexer_data->next;
	}
	return 1;
}

int are_pipes_valid(t_token *lexer_data) {
	int wait_for_command;

	wait_for_command = 0;
	while (lexer_data)
	{
		if (wait_for_command && lexer_data->type != COMMAND)
			return 0;
		if (lexer_data->type == PIPE)
			wait_for_command = 1;
		else if (lexer_data->type == COMMAND)
			wait_for_command = 0;
		lexer_data = lexer_data->next;
	}
	return wait_for_command == 0;
}


int is_valid(const char *input, t_token *lexer_data) {
	return are_quotes_valid(input, lexer_data) &&
		are_redirections_valid(lexer_data) &&
		are_pipes_valid(lexer_data);
}