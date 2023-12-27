#include "libft/libft.h"
#include "parser.h"
#include <stdio.h>
#include "utils.h"

/**
 * get token type from meta character
 * @param input the input string
 * @return the token type
 */
t_token_type get_meta_token_type(const char *input) {
	if (!input || !*input)
		return UNKNOWN;
	if (input[0] == '>') {
		if (input[1] == '>')
			return APPEND_REDIRECTION;
		return OUTPUT_REDIRECTION;
	}
	if (input[0] == '<') {
		if (input[1] == '<')
			return HEREDOC_REDIRECTION;
		return INPUT_REDIRECTION;
	}
	if (input[0] == '|')
		return PIPE;
	return UNKNOWN;
}

/**
 * state for command name
 *
 * Example:
 * 		cmd1 arg1
 * 		^
 * 		cmd1 arg1 | cmd2
 * 		^			^
 * 		cmd1 | cmd2
 * 		^      ^
 * @param lexer_data the lexer data to append new token
 * @param input the input string
 * @param index the index of the first char of the command name
 * @return the next state
 */
state command_state(t_token **lexer_data, char *input, int index)
{
	//assume input and lexer_data is non-null
	//assume 0 < index < strlen(input)
	t_token token;
	token.start = index;
	while (input[index] && is_name_char(input[index]))
		index++;
	if (index == token.start)
		return unexpected_token_error(input[index]), NULL;
	token.end = index - 1;
	token.type = COMMAND;
	lexer_data_append(lexer_data, lexer_data_new(token));
	return (state) command_after_state;
}

/**
 * state for everything after command name
 *
 * Example:
 * 		cmd1 arg1
 * 			 ^
* 		cmd1 arg1 | cmd2
 * 			 ^
 * 		cmd1 | cmd2
 * 			 ^
 * 		cmd1 < infile
 * 			 ^
 *
 * @param lexer_data the lexer data to append new token
 * @param input the input string
 * @param index the index of the first char that is not whitespace after command name.
 * @return the next state
 */
state command_after_state(t_token **lexer_data, char *input, int index)
{
	if (input[index] == '\0')
		return NULL;
	if (is_meta_char(input[index]))
		return (state) delimiter_state;
	return (state) argument_state;
}

/**
 * state for arguments
 *
 * Example:
 * 		cmd1 arg1
 * 			 ^
 * 		cmd1 "arg1"
 * 			 ^
 * 		cmd1 'arg1'
 * 			 ^
 * 		cmd1 -option
 * 			 ^
 *
 * @param lexer_data the lexer data to append new token
 * @param input the input string
 * @param index the index of the first char of the argument (included quotes)
 * @return the next state
 */
state argument_state(t_token **lexer_data, char *input, int index) {
	//assume input and lexer_data is non-null
	//assume 0 < index < strlen(input) 
	//assume input[index] is not a null, whitespace or metacharacter.
	t_token token;
	token.start = index;
	if (input[index] == DOUBLE_QUOTE)
	{
		token.type = DOUBLE_QUOTED_ARGUMENT;
		index += find_char(&input[index + 1], DOUBLE_QUOTE) + 1;
	}
	else if (input[index] == SINGLE_QUOTE)
	{
		token.type = SINGLE_QUOTED_ARGUMENT;
		index += find_char(&input[index + 1], SINGLE_QUOTE) + 1;
	}
	else
	{
		token.type = UNQUOTED_ARGUMENT;
		while (input[index] != '\0' && is_name_char(input[index]))
			index++;
		index--;
	}
	token.end = index;
	lexer_data_append(lexer_data, lexer_data_new(token));
	return (state) command_after_state;
}

/**
 * state for metacharacters
 * Example:
 * 		cmd arg1 | cmd2
 * 				 ^
 *		cmd arg1 > outfile
 *			 	 ^
 *		cmd < infile
 *			^
 *		cmd << heredoc
 *			^
 *		cmd arg1 >> outfile
 *		 		 ^
 * @param lexer_data the lexer data to append new token
 * @param input the input string
 * @param index the index of the first char of the metacharacter
 * @return the next state
 */
state delimiter_state(t_token **lexer_data, char *input, int index)
{
	t_token_type type;
	int length;
	t_token token;

	type = get_meta_token_type(&input[index]);
	if (type == PIPE || type == OUTPUT_REDIRECTION || type == INPUT_REDIRECTION)
		length = 1;
	else if (type == APPEND_REDIRECTION || type == HEREDOC_REDIRECTION)
		length = 2;
	else
		return NULL; //do not append new token if command name not found.
	token.start = index;
	token.end = index + length - 1;
	token.type = type;
	lexer_data_append(lexer_data, lexer_data_new(token));
	if (type == PIPE)
		return (state) command_state;
	return (state) redirection_word_state;
}

/**
 *
 * state for words after redirection
 * Example:
 * 		cmd arg1 > outfile arg2
 *                 ^
 *      cmd < infile arg1
 *      	  ^
 *      cmd << heredoc
 *      	   ^
 *     	cmd arg1 >> outfile arg2
 *     			    ^
 *
 * @param lexer_data the lexer data to append new token
 * @param input the input string
 * @param index the index of the first char of the word
 * @return the next state
 */
state redirection_word_state(t_token **lexer_data, char *input, int index)
{
	t_token token;
	token.start = index;
	token.type = WORD;
	if (is_quote(input[index])) {
		index += find_char(&input[index + 1], input[index]) + 1;
	} else {
		while (input[index] && is_name_char(input[index]))
			index++;
		index--;
	}
	token.end = index;
	if (token.end < token.start)
		return unexpected_token_error(input[index]), NULL;
	lexer_data_append(lexer_data, lexer_data_new(token));
	return (state) command_after_state;
}

/*
 * get end index of last token
 * (index of last char of scanned part of input)
 */
int get_index(t_token *token) {
	t_token *last_token = NULL;
	last_token = get_last_lexer_data(token);
	if (!last_token)
		return 0;
	return last_token->end + 1;
}

t_token *lexer(char *input) {
	t_token *token = NULL;
	state next_state = (state) command_state;
	int index;
	while (next_state) {
		index = get_index(token);
		index += skip_white_spaces(&input[index]);
		if (input[index] == '\0')
			break;
		next_state = (state) next_state(&token, input, index);
	}
	return token;
}
