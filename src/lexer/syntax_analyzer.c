/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:18:35 by facetint          #+#    #+#             */
/*   Updated: 2024/03/14 16:08:12 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include "../../includes/char_classification.h"
#include "../../includes/utils.h"

int is_word(t_token_type type)
{
	return type == UNQUOTED_WORD ||
		   type == SINGLE_QUOTED_WORD ||
		   type == DOUBLE_QUOTED_WORD;
}

/**
 * check if the token is an operator (redirection operator or pipe)
 * @param type the token type
 * @return 1 if the token is an operator, 0 otherwise
 */
int is_operator(t_token_type type)
{
	return type == HEREDOC_REDIRECTION ||
		   type == INPUT_REDIRECTION ||
		   type == OUTPUT_REDIRECTION ||
		   type == APPEND_REDIRECTION ||
		   type == PIPE;
}

int is_there_lack_of_word(t_token *lexer_data)
{
	int wait_for_word;

	wait_for_word = 0;
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

int are_quotes_valid(t_token *lexer_data)
{
	unsigned int length;

	while (lexer_data)
	{
		if (lexer_data->type == SINGLE_QUOTED_WORD)
		{
			length = ft_strlen(lexer_data->value);
			if (length <= 1
				|| lexer_data->value[0] != SINGLE_QUOTE
				|| lexer_data->value[length - 1] != SINGLE_QUOTE
				|| is_escaped(lexer_data->value, length - 1))
				return (0);
		}
		else if (lexer_data->type == DOUBLE_QUOTED_WORD)
		{
			length = ft_strlen(lexer_data->value);
			if (length <= 1
				|| lexer_data->value[0] != DOUBLE_QUOTE
				|| lexer_data->value[length - 1] != DOUBLE_QUOTE
				|| is_escaped(lexer_data->value, length - 1))
				return (0);
		}
		lexer_data = lexer_data->next;
	}
	return (1);
}

int are_tokens_valid(t_token *lexer_data)
{
	while (lexer_data)
	{
		if (lexer_data->type == UNKNOWN)
			return 0;
		if (is_word(lexer_data->type) && lexer_data->value == NULL)
			return 0;
		lexer_data = lexer_data->next;
	}
	return 1;
}

int is_valid(t_token *lexer_data) {
	return are_tokens_valid(lexer_data)
		   && are_quotes_valid(lexer_data)
		   && is_there_lack_of_word(lexer_data);
}
