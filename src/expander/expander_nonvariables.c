/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_nonvariables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:17:36 by facetint          #+#    #+#             */
/*   Updated: 2024/03/28 17:01:01 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/utils.h"
#include "../../libft/libft.h"
#include "../../includes/char_classification.h"
#include "../../memory-allocator/allocator.h"
#include <stdio.h>

void insert_uword_tokens(t_token **token_ptr, char **strings)
{
	t_token *token;
	t_token *list;
	t_token *new;
	int i;

	token = *token_ptr;
	token->value = strings[0];
	list = NULL;
	i = 1; 
	while (strings[i])
	{
		new = lexer_data_new((t_token) {.type = DELIMITER, .next = NULL, .value = NULL});
		lexer_data_append(&list, new);
		new = lexer_data_new((t_token) {.type = UNQUOTED_WORD, .next = NULL, .value = strings[i]});
		lexer_data_append(&list, new);
		i++;
	}
	lexer_data_insert(token, list);
}

