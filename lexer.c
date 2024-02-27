#include "libft/libft.h"
#include "includes/minishell.h"
#include <stdio.h>
#include "includes/utils.h"
#include "includes/char_classification.h"

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

lexer_state word_state(t_token **lexer_data, char *input, int *const index)
{
	t_token token;
	int start_index;

	start_index = *index;
	if (input[*index] == DOUBLE_QUOTE)
	{
		token.type = DOUBLE_QUOTED_WORD;
		*index += find_char(&input[*index + 1], DOUBLE_QUOTE) + 1;
	}
	else if (input[*index] == SINGLE_QUOTE)
	{
		token.type = SINGLE_QUOTED_WORD;
		*index += find_char(&input[*index + 1], SINGLE_QUOTE) + 1;
	}
	else
	{
		token.type = UNQUOTED_WORD;
		while (input[*index] && (is_unquoted_word_char(input[*index]) || is_escaped(input, *index)))
			(*index)++;
		(*index)--;
	}
	token.value = ft_substr(input, start_index, *index - start_index + 1);
	if (ft_strlen(token.value) > 0)
		lexer_data_append(lexer_data, lexer_data_new(token));
	return ((lexer_state) delimiter_state);
}

/**
 * state for operators
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
 * @param index the index of the first char of the a operator
 * @return the next state
 */
lexer_state operator_state_l(t_token **lexer_data, char *input, int *const index)
{
	int length;
	t_token token;

	token.type = get_meta_token_type(&input[*index]);
	if (token.type == PIPE || token.type == OUTPUT_REDIRECTION || token.type == INPUT_REDIRECTION)
		length = 1;
	else if (token.type == APPEND_REDIRECTION || token.type == HEREDOC_REDIRECTION)
		length = 2;
	else
		return NULL; // do not append new token
	*index = *index + length - 1; // to mark where we stopped scanning
	token.value = NULL;
	lexer_data_append(lexer_data, lexer_data_new(token));
	return ((lexer_state) delimiter_state);
}

lexer_state delimiter_state(t_token **lexer_data, char *input, int *const index)
{
	t_token token;
	int skipped_spaces;
	char next_non_whitespace;

	skipped_spaces = skip_white_spaces(&input[*index]);
	next_non_whitespace = input[*index + skipped_spaces];
	if (next_non_whitespace == '\0')
		return NULL;
	if (skipped_spaces != 0)
	{
		*index = *index + skipped_spaces - 1; // to mark where we stopped scanning
		token.value = NULL;
		token.type = DELIMITER;
		lexer_data_append(lexer_data, lexer_data_new(token));
	}
	else
	{
		*index = *index - 1;
	}
	if (is_meta_char(next_non_whitespace))
		return (lexer_state) operator_state_l;
	return ((lexer_state) word_state);
}

t_token *lex(char *input)
{
	t_token *token = NULL;
	lexer_state next_state = (lexer_state) word_state;
	int index;

	index = skip_white_spaces(input);
	while (next_state && input[index])
	{
		next_state = (lexer_state) next_state(&token, input, &index);
		index++;
	}
	return (token);
}
