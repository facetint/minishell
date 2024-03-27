/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:17:39 by facetint          #+#    #+#             */
/*   Updated: 2024/03/26 11:21:04 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/utils.h"
#include "../../libft/libft.h"
#include "../../includes/char_classification.h"
#include "../../memory-allocator/allocator.h"
#include "../../includes/env.h"
#include <stdio.h>

/**
 * replaces the string at input with replacement.
 *
 * @param input input string
 * @param p_start start index of the string to replace (placeholder start index)
 * @param p_len length of the string to replace (placeholder length)
 * @param replacement replacement string
 */
char	*replace_string(char *input, int p_start, int p_len, char *replacement)
{
	char *head;
	char *tail;
	char *result;
	
	head = ft_substr(input, 0, p_start);
	tail = ft_substr(input, p_start + p_len + 1, ft_strlen(input) - p_start - p_len);
	if (replacement == NULL)
		result = ft_str_arr_join((char *[]) {head, tail}, 2);
	else
		result = ft_str_arr_join((char *[]) {head, replacement, tail}, 3);
	safe_free(head);
	safe_free(tail);
	return result;
}

/**
 * expands the variable at index in input.
 *
 * Example:
 * $USER = "bsq"
 * input = "hello $USER"
 * index = 6
 * returns -> 8
 *
 * @param input input string
 * @param index index of the variable (must point to '$')
 * @return length of string before variable + expanded variable length - 1
 * this return value points to where you should continue for next variable.
 */
int	expand_variable(char **input, int index)
{
	char	*str;
	char	*varname;
	char	*new;
	int 	str_len;
	int		varname_len;

	str = *input;
	varname_len = count_len(&str[index + 1], is_a_name_char);
	if (varname_len == 0)
		return index;
	varname = ft_substr(str, index + 1, varname_len);
	str_len = (int) ft_strlen(str);
	new = replace_string(str, index, varname_len, find_env(varname));
	*input = new;
	safe_free(varname);
	safe_free(str);
	return index + varname_len + (int) ft_strlen(new) - str_len;
}

int expand_exit_status(char **input, int index)
{
	int		exit_status;
	char	*new;
	int		input_len;
	
	input_len = (int) ft_strlen(*input);
	exit_status = *get_exit_status();
	new = replace_string(*input, index, 1, ft_itoa(exit_status));
	safe_free(*input);
	*input = new;
	return index + 1 + ((int) ft_strlen(new)) - input_len;
}

void	expand_string(char **string)
{
	int index;
	char *str;

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
/*
 * Expandable variable but its name length is zero.
 * Example: $"USER" -> USER 
*/
int is_empty_variable(t_token *token)
{
	return ft_strcmp(token->value, "$") == 0 && token->next && is_word(token->next->type);
}
void	expand(t_token **head)
{
	t_token *token;
	t_token **next_ptr;

	token = *head;
	next_ptr = head;
	while (token)
	{
		/* only unquoted word and double-quoted word tokens are expandable. */
		if (token->type == UNQUOTED_WORD || token->type == DOUBLE_QUOTED_WORD)
		{
			/* do not expand single $ */
			if (is_empty_variable(token)) {
				token->value = ft_strdup("");
			} else {
				expand_string(&token->value);
				/* only unquoted words are not protected for the split */
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
	t_token	*token = *token_ptr;

	new_words = str_split(token->value, is_internal_field_sep);
	if (str_arr_size(new_words) == 1)
		return; /* there is no new word */
	safe_free(token->value);
	insert_uword_tokens(token_ptr, new_words);
	safe_free(new_words);
}
