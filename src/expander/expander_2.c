/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 17:50:47 by facetint          #+#    #+#             */
/*   Updated: 2024/04/01 17:50:59 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/utils.h"
#include "../../libft/libft.h"

void	expand_token(t_token *token, t_token **head,
		t_token **token_ptr, t_token **prev_ptr, t_token**next_token_ptr)
{
	if (is_nameless_variable(token))
		token->value = ft_strdup("");
	else
	{
		int isvar = token->value[0] == '$';
		expand_string(&token->value);
		if (is_full_of_spaces(token->value))
			remove_token(prev_ptr, head, token);
		else if ((token->type == UNQUOTED_WORD && isvar))
			internal_field_split(token_ptr, next_token_ptr);
	}
}
