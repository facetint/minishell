/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_nonvariables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:17:36 by facetint          #+#    #+#             */
/*   Updated: 2024/03/14 16:06:57 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/utils.h"
#include "../../libft/libft.h"
#include "../../includes/char_classification.h"
#include "../../memory-allocator/allocator.h"
#include <stdio.h>

/**
 * Removes the token from the list and inserts unquoted word tokens in its place.
 * 
 * Example:
 *                  k    l    m
 * assume we have: UW D UW D UW
 * and we call this function with the token 'l'
 * with the strings: {"a", "b", "c", "d"}
 * 
 *                                   a    b    c    d
 * 1. a token list will be created: UW D UW D UW D UW
 * 2. the token 'l' will be removed.
 * 3. the token list will be inserted in place of the removed token.
 *          k    a    b    c	d    m
 * Result: UW D UW D UW D UW D UW D UW
 *              ~~~~~~~~~~~~~~~~~
*/
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

