/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcoskun <hcoskun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:17:39 by facetint          #+#    #+#             */
/*   Updated: 2024/03/30 16:20:53 by hcoskun          ###   ########.fr       */
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
	varname_len = count_len(&str[index + 1], is_a_name_char);
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
	t_token	**next_ptr;

	token = *head;
	next_ptr = head;
	while (token)
	{
		if (token->type == UNQUOTED_WORD || token->type == DOUBLE_QUOTED_WORD)
		{
			if (is_empty_variable(token))
				token->value = ft_strdup("");
			else
			{
				expand_string(&token->value);
				if (token->type == UNQUOTED_WORD)
					internal_field_split(next_ptr);
			}
		}
		next_ptr = &token->next;
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
