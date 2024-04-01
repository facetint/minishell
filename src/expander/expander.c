/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:17:39 by facetint          #+#    #+#             */
/*   Updated: 2024/04/01 08:00:15 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/utils.h"
#include "../../libft/libft.h"
#include "../../includes/char_classification.h"
#include "../../memory-allocator/allocator.h"
#include "../../includes/env.h"

int	expand_variable(char **input, int index)
{
	char	*str;
	char	*varname;
	char	*new;
	int		str_len;
	int		varname_len;

	str = *input;
	varname_len = count_len(&str[index + 1], is_name_char);
	if (varname_len == 0)
		return (index);
	varname = ft_substr(str, index + 1, varname_len);
	str_len = (int) ft_strlen(str);
	new = replace_string(str, index, varname_len, find_env(varname));
	*input = new;
	safe_free(varname);
	safe_free(str);
	return (index + varname_len + (int) ft_strlen(new) - str_len);
}

int	expand_exit_status(char **input, int index)
{
	int		exit_status;
	char	*new;
	int		input_len;

	input_len = (int) ft_strlen(*input);
	exit_status = *get_exit_status();
	new = replace_string(*input, index, 1, ft_itoa(exit_status));
	safe_free(*input);
	*input = new;
	return (index + 1 + ((int) ft_strlen(new)) - input_len);
}

void	expand_string(char **string)
{
	int		index;
	char	*str;

	str = *string;
	index = 0;
	while (str[index])
	{
		if (str[index] == '$')
		{
			if (str[index + 1] == '?')
				index = expand_exit_status(&str, index);
			else
				index = expand_variable(&str, index);
		}
		index++;
	}
	*string = str;
}

void	expand(t_token **head)
{
	t_token	*token;
	t_token	**token_ptr;
	t_token	**prev_ptr;

	token = *head;
	token_ptr = head;
	prev_ptr = NULL;
	while (token)
	{
		if (token->type == UNQUOTED_WORD || token->type == DOUBLE_QUOTED_WORD)
		{
			if (is_nameless_variable(token))
				token->value = ft_strdup("");
			else
			{
				expand_string(&token->value);
				if (is_full_of_spaces(token->value))
				{
					if (prev_ptr == NULL)
						*head = token->next;
					else
						(*prev_ptr)->next = token->next;
				}
				else if (token->type == UNQUOTED_WORD)
					internal_field_split(token_ptr);
			}
		}
		prev_ptr = token_ptr;
		token_ptr = &token->next;
		token = token->next;
	}
}

void	internal_field_split(t_token **token_ptr)
{
	char	**new_words;
	t_token	*token;

	token = *token_ptr;
	new_words = str_split(token->value, is_internal_field_sep);
	if (str_arr_size(new_words) == 1)
		return ;
	safe_free(token->value);
	insert_uword_tokens(token_ptr, new_words);
	safe_free(new_words);
}
