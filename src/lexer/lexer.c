/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:17:52 by facetint          #+#    #+#             */
/*   Updated: 2024/04/02 17:23:42 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../includes/minishell.h"
#include <stdio.h>
#include "../../includes/utils.h"
#include "../../includes/char_classification.h"

t_token_type	get_meta_token_type(const char *input)
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

t_lexer_state	word_state(t_token **lexer_data, char *input, int *const i)
{
	t_token	token;
	int		start_i;

	start_i = *i;
	if (input[*i] == DOUBLE_QUOTE)
	{
		token.type = DOUBLE_QUOTED_WORD;
		*i += find_char(&input[*i + 1], DOUBLE_QUOTE) + 1;
	}
	else if (input[*i] == SINGLE_QUOTE)
	{
		token.type = SINGLE_QUOTED_WORD;
		*i += find_char(&input[*i + 1], SINGLE_QUOTE) + 1;
	}
	else
	{
		token.type = UNQUOTED_WORD;
		while (is_unquoted_word_char(input[*i]) || is_escaped(input, *i))
			(*i)++;
		(*i)--;
	}
	token.value = ft_substr(input, start_i, *i - start_i + 1);
	if (ft_strlen(token.value) > 0)
		lexer_data_append(lexer_data, lexer_data_new(token));
	return ((t_lexer_state) delimiter_state);
}

t_lexer_state	operator_state_l(t_token **lexer_data,
	char *input, int *const i)
{
	int		length;
	t_token	token;

	token.type = get_meta_token_type(&input[*i]);
	if (token.type == PIPE || token.type == OUTPUT_REDIRECTION
		|| token.type == INPUT_REDIRECTION)
		length = 1;
	else if (token.type == APPEND_REDIRECTION
		|| token.type == HEREDOC_REDIRECTION)
		length = 2;
	else
		return (NULL);
	*i = *i + length - 1;
	token.value = NULL;
	lexer_data_append(lexer_data, lexer_data_new(token));
	return ((t_lexer_state) delimiter_state);
}

t_lexer_state	delimiter_state(t_token **lexer_data, char *input, int *const i)
{
	t_token		token;
	int			skipped_spaces;
	char		next_non_whitespace;

	skipped_spaces = skip_white_spaces(&input[*i]);
	next_non_whitespace = input[*i + skipped_spaces];
	if (next_non_whitespace == '\0')
		return (NULL);
	if (skipped_spaces != 0)
	{
		*i = *i + skipped_spaces - 1;
		token.value = NULL;
		token.type = DELIMITER;
		lexer_data_append(lexer_data, lexer_data_new(token));
	}
	else
		*i = *i - 1;
	if (is_meta_char(next_non_whitespace))
		return ((t_lexer_state) operator_state_l);
	return ((t_lexer_state) word_state);
}

t_token	*lex(char *input)
{
	int				i;
	t_token			*token;
	t_lexer_state	next_state;

	next_state = (t_lexer_state) word_state;
	token = NULL;
	i = skip_white_spaces(input);
	while (next_state && input[i])
	{
		next_state = (t_lexer_state) next_state(&token, input, &i);
		i++;
	}
	return (token);
}
