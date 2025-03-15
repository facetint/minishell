/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 17:04:35 by facetint          #+#    #+#             */
/*   Updated: 2024/03/29 17:14:43 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include "../../includes/char_classification.h"
#include "../../includes/utils.h"

int	are_quotes_valid(t_token *token)
{
	unsigned int	length;

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

int	are_tokens_valid(t_token *lexer_data)
{
	while (lexer_data)
	{
		if (lexer_data->type == UNKNOWN)
			return (0);
		if (is_word(lexer_data->type) && lexer_data->value == NULL)
			return (0);
		lexer_data = lexer_data->next;
	}
	return (1);
}

int	is_valid(t_token *lexer_data)
{
	return (are_tokens_valid(lexer_data)
		&& is_there_lack_of_word(lexer_data)
		&& validate_pipes(lexer_data));
}
