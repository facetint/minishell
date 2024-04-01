/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 17:36:24 by facetint          #+#    #+#             */
/*   Updated: 2024/04/01 15:43:13 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../includes/minishell.h"
#include "../../includes/utils.h"
#include "../../memory-allocator/allocator.h"

void	join_all_composed_words(t_token **cur_token, char **string_ptr)
{
	char	*new_name;
	t_token	*lexer_data;

	lexer_data = *cur_token;
	lexer_data = skip_delimiters(lexer_data);
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

int	count_cmd_args(t_token *token)
{
	int	arg_count;

	arg_count = 0;
	while (token && token->type != PIPE)
	{
		if (is_operator(token->type))
		{
			while (token && !is_word(token->type))
				token = token->next;
			if (token)
				token = token->next;
			continue ;
		}
		token = skip_delimiters(token);
		if (token && is_word(token->type))
		{
			while (token && is_word(token->type))
				token = token->next;
			arg_count++;
		}
		if (token)
			token = token->next;
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

t_token	*skip_delimiters(t_token *token)
{
	while (token && token->type == DELIMITER)
		token = token->next;
	return (token);
}
