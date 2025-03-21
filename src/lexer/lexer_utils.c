/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:17:50 by facetint          #+#    #+#             */
/*   Updated: 2024/03/31 06:16:03 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../memory-allocator/allocator.h"
#include <stdlib.h>

t_token	*get_last_lexer_data(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->next)
		token = token->next;
	return (token);
}

t_token	*lexer_data_new(t_token token)
{
	t_token	*data;

	data = safe_malloc(sizeof(t_token));
	*data = token;
	data->next = NULL;
	return (data);
}

void	lexer_data_insert(t_token *data, t_token *new_list)
{
	t_token	*last;

	if (!data || !new_list)
		return ;
	last = get_last_lexer_data(new_list);
	last->next = data->next;
	data->next = new_list;
}

void	lexer_data_append(t_token **data, t_token *new_data)
{
	t_token	*cur_data;

	if (*data == NULL)
	{
		*data = new_data;
		return ;
	}
	cur_data = *data;
	while (cur_data->next != NULL)
		cur_data = cur_data->next;
	cur_data->next = new_data;
}

void	uninit_tokens(t_token *lexical_data)
{
	t_token	*next;

	while (lexical_data)
	{
		next = lexical_data->next;
		if (is_word(lexical_data->type))
			safe_free(lexical_data->value);
		safe_free(lexical_data);
		lexical_data = next;
	}
}

t_token **find_token_ptr_before(t_token **head, t_token *tofind)
{
	t_token **prev = NULL;
	t_token **cur = head;

	while (*cur && *cur != tofind) {	
		prev = cur;
		cur = &((*cur)->next);
	}
	return prev;
}