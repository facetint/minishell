/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:18:35 by facetint          #+#    #+#             */
/*   Updated: 2024/03/29 17:13:54 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include "../../includes/char_classification.h"
#include "../../includes/utils.h"

int	is_word(t_token_type type)
{
	return (type == UNQUOTED_WORD ||
		type == SINGLE_QUOTED_WORD ||
		type == DOUBLE_QUOTED_WORD);
}

int	is_operator(t_token_type type)
{
	return (type == HEREDOC_REDIRECTION ||
		type == INPUT_REDIRECTION ||
		type == OUTPUT_REDIRECTION ||
		type == APPEND_REDIRECTION ||
		type == PIPE);
}

int	is_there_lack_of_word(t_token *token)
{
	int	wait_for_word;

	wait_for_word = 0;
	while (token)
	{
		if (token->type == DELIMITER)
			token = token->next;
		if (wait_for_word && !is_word(token->type))
			return (0);
		if (is_word(token->type))
			wait_for_word = 0;
		else if (is_operator(token->type))
			wait_for_word = 1;
		token = token->next;
	}
	return (wait_for_word == 0);
}

int	validate_pipes(t_token *token)
{
	int	args;

	args = 0;
	while (token)
	{
		if (is_word(token->type))
		{
			args++;
			token = token->next;
			continue ;
		}

		if (is_operator(token->type) && token->type != PIPE)
		{
			token = token->next;
			if (token && token->type == DELIMITER)
				token = token->next;
			if (!token || !is_word(token->type))
				return (0);
			token = token->next;
			continue ;
		}
		if (token->type == PIPE)
		{
			if (args == 0)
				return (0);
			args = 0;
		}
		token = token->next;
	}
	return (1);
}
