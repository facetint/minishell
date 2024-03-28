/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:18:35 by facetint          #+#    #+#             */
/*   Updated: 2024/03/28 16:58:07 by facetint         ###   ########.fr       */
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

int is_operator(t_token_type type)
{
	return type == HEREDOC_REDIRECTION ||
		   type == INPUT_REDIRECTION ||
		   type == OUTPUT_REDIRECTION ||
		   type == APPEND_REDIRECTION ||
		   type == PIPE;
}

int is_there_lack_of_word(t_token *token)
{
	int wait_for_word;

	wait_for_word = 0;
	while (token)
	{
		if (token->type == DELIMITER)
			token = token->next;
		if (wait_for_word && !is_word(token->type))
			return 0;
		if (is_word(token->type))
			wait_for_word = 0;
		else if (is_operator(token->type))
			wait_for_word = 1;
		token = token->next;
	}
	return wait_for_word == 0;
}

int	validate_pipes(t_token *token)
{
	int args;

	args = 0;
	while (token)
	{
		if (is_word(token->type))
		{
			args++;
			token = token->next;
			continue;
		}

		if (is_operator(token->type) && token->type != PIPE)
		{
			token = token->next;
			if (token && token->type == DELIMITER)
				token = token->next;
			if (!token || !is_word(token->type))
				return 0;
			token = token->next;
			continue;
		}

		if (token->type == PIPE)
		{
			if (args == 0)
				return 0;
			args = 0;
		}
		token = token->next;
	}
	return 1;
}

int are_quotes_valid(t_token *token)
{
	unsigned int length;

	while (token)
	{
		if (token->type == SINGLE_QUOTED_WORD)
		{
			length = ft_strlen(token->value);
			if (length <= 1
				|| token->value[0] != SINGLE_QUOTE
				|| token->value[length - 1] != SINGLE_QUOTE)
				return (0);
		}
		else if (token->type == DOUBLE_QUOTED_WORD)
		{
			length = ft_strlen(token->value);
			if (length <= 1
				|| token->value[0] != DOUBLE_QUOTE
				|| token->value[length - 1] != DOUBLE_QUOTE
				|| is_escaped(token->value, length - 1))
				return (0);
		}
		token = token->next;
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
		   && is_there_lack_of_word(lexer_data)
		   && validate_pipes(lexer_data);
}
