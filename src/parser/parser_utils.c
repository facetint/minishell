/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 17:36:24 by facetint          #+#    #+#             */
/*   Updated: 2024/03/31 06:15:31 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../includes/minishell.h"
#include "../../includes/utils.h"
#include "../../memory-allocator/allocator.h"
#include <stdio.h>

void	join_all_composed_words(t_token **cur_token, char **string_ptr)
{
	char	*new_name;
	t_token	*lexer_data;

	lexer_data = *cur_token;
	if (lexer_data->type == DELIMITER)
		lexer_data = lexer_data->next;
	while (lexer_data && is_word(lexer_data->type))
	{
		new_name = ft_strjoin(*string_ptr, lexer_data->value);
		if (*string_ptr)
			safe_free(*string_ptr);
		*string_ptr = new_name;
		lexer_data = lexer_data->next;
	}
	*cur_token = lexer_data;
}

t_redirection	create_redirection_data(t_token **lexer_data)
{
	t_redirection	redirection;

	redirection = (t_redirection){0};
	if ((*lexer_data)->type == INPUT_REDIRECTION)
		redirection.flags = INPUT;
	else if ((*lexer_data)->type == HEREDOC_REDIRECTION)
		redirection.flags = HEREDOC | INPUT;
	else if ((*lexer_data)->type == APPEND_REDIRECTION)
		redirection.flags = APPEND;
	*lexer_data = (*lexer_data)->next;
	join_all_composed_words(lexer_data, &redirection.redirected);
	return (redirection);
}

int	count_cmd_args(t_token *lexer_data)
{
	int	arg_count;

	arg_count = 0;
	while (lexer_data && lexer_data->type != PIPE)
	{
		if (is_operator(lexer_data->type))
		{
			while (lexer_data && !is_word(lexer_data->type))
				lexer_data = lexer_data->next;
			if (lexer_data)
				lexer_data = lexer_data->next;
			continue ;
		}
		if (lexer_data->type == DELIMITER)
			lexer_data = lexer_data->next;
		if (lexer_data && is_word(lexer_data->type))
		{
			while (lexer_data && is_word(lexer_data->type))
				lexer_data = lexer_data->next;
			arg_count++;
		}
		if (lexer_data)
			lexer_data = lexer_data->next;
	}
	return (arg_count);
}

int	count_cmd_redirections(t_token *lexer_data)
{
	int	redirection_count;

	redirection_count = 0;
	while (lexer_data && lexer_data->type != PIPE)
	{
		if (is_operator(lexer_data->type) && lexer_data->type != PIPE)
			redirection_count++;
		lexer_data = lexer_data->next;
	}
	return (redirection_count);
}
