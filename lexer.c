#include "libft/libft.h"
#include "parser.h"
#include <stdio.h>
#include "utils.h"

/**
 * get token type from meta character
 * @param input the input string
 * @return the token type
 */
t_token_type get_meta_token_type(const char *input)
{
	if (!input || !*input)
		return (UNKNOWN);
	if (input[0] == '>')
	{
		if (input[1] == '>')
			return (APPEND_REDIRECTION);
		return (OUTPUT_REDIRECTION);
	}
	if (input[0] == '<')
	{
		if (input[1] == '<')
			return (HEREDOC_REDIRECTION);
		return (INPUT_REDIRECTION);
	}
	if (input[0] == '|')
		return (PIPE);
	return (UNKNOWN);
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
lexer_state word_state(t_token **lexer_data, char *input, int index) {
	//assume input and lexer_data is non-null
	//assume 0 < index < strlen(input) 
	//assume input[index] is not a null, whitespace or metacharacter.
	t_token token;
	int start_index;

	start_index = index;
	if (input[index] == DOUBLE_QUOTE)
	{
		token.type = DOUBLE_QUOTED_WORD;
		index += find_char(&input[index + 1], DOUBLE_QUOTE) + 1;
	}
	else if (input[index] == SINGLE_QUOTE)
	{
		token.type = SINGLE_QUOTED_WORD;
		index += find_char(&input[index + 1], SINGLE_QUOTE) + 1;
	}
	else
	{
		token.type = UNQUOTED_WORD;
		while (input[index] && (is_unquoted_word_char(input[index]) || is_escaped(input, index)))
			index++;
		index--;
	}
	token.end = index; // to mark where we stopped scanning
	token.value = ft_substr(input, start_index, index - start_index + 1);
	lexer_data_append(lexer_data, lexer_data_new(token));
	return (lexer_state) delimiter_state;
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
lexer_state meta_state(t_token **lexer_data, char *input, int index)
{
	int length;
	t_token token;

	token.type = get_meta_token_type(&input[index]);
	if (token.type == PIPE || token.type == OUTPUT_REDIRECTION || token.type == INPUT_REDIRECTION)
		length = 1;
	else if (token.type == APPEND_REDIRECTION || token.type == HEREDOC_REDIRECTION)
		length = 2;
	else
		return NULL; //do not append new token
	token.end = index + length - 1; // to mark where we stopped scanning
	token.value = NULL;
	lexer_data_append(lexer_data, lexer_data_new(token));
	return (lexer_state) delimiter_state;
}

lexer_state delimiter_state(t_token **lexer_data, char *input, int index)
{
	t_token token;
	int skipped_spaces;
	char next_non_whitespace;

	skipped_spaces = skip_white_spaces(&input[index]);
	next_non_whitespace = input[index + skipped_spaces];
	if (next_non_whitespace == '\0')
		return NULL;
	if (skipped_spaces != 0)
	{
		token.end = index + skipped_spaces - 1; // to mark where we stopped scanning
		token.value = NULL;
		token.type = DELIMITER;
		lexer_data_append(lexer_data, lexer_data_new(token));
	}

	if (is_meta_char(next_non_whitespace))
		return (lexer_state) meta_state;
	return (lexer_state) word_state;
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
	lexer_state next_state = (lexer_state) word_state;
	int index;
	while (next_state) {
		index = get_index(token);
		if (input[index] == '\0')
			break;
		next_state = (lexer_state) next_state(&token, input, index);
	}
	return token;
}
