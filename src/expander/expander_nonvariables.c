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

void	insert_uword_tokens(t_token **token_ptr, char **strings)
{
	t_token	*token;
	t_token	*list;
	t_token	*new;
	int		i;

	token = *token_ptr;
	token->value = strings[0];
	list = NULL;
	i = 1;
	while (strings[i])
	{
		new = lexer_data_new((t_token){NULL, DELIMITER, NULL});
		lexer_data_append(&list, new);
		new = lexer_data_new((t_token){strings[i], UNQUOTED_WORD, NULL});
		lexer_data_append(&list, new);
		i++;
	}
	lexer_data_insert(token, list);
}

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
