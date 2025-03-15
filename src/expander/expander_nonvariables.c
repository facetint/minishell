/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_nonvariables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:17:36 by facetint          #+#    #+#             */
/*   Updated: 2024/04/01 15:41:31 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/utils.h"
#include "../../libft/libft.h"
#include "../../includes/char_classification.h"
#include "../../memory-allocator/allocator.h"

int	is_nameless_variable(t_token *token)
{
	return (ft_strcmp(token->value, "$") == 0
		&& token->next && is_word(token->next->type));
}

char	*replace_string(char *input, int p_start, int p_len, char *replacement)
{
	char	*head;
	char	*tail;
	char	*result;

	head = ft_substr(input, 0, p_start);
	tail = ft_substr(input, p_start + p_len
			+ 1, ft_strlen(input) - p_start - p_len);
	if (replacement == NULL)
		result = ft_str_arr_join((char *[]){head, tail}, 2);
	else
		result = ft_str_arr_join((char *[]){head, replacement, tail}, 3);
	safe_free(head);
	safe_free(tail);
	return (result);
}
