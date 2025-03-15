/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:17:39 by facetint          #+#    #+#             */
/*   Updated: 2024/04/01 17:46:58 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/utils.h"
#include "../../libft/libft.h"
#include "../../includes/char_classification.h"
#include "../../memory-allocator/allocator.h"
#include "../../includes/env.h"
#include <stdio.h>

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
			expand_token(token, head, token_ptr, prev_ptr, &token);
		prev_ptr = token_ptr;
		token_ptr = &token->next;
		token = token->next;
	}
}

t_token		*do_ifs(char *str)
{
	//printf("do_ifs: %s\n", str);
	int len = ft_strlen(str);
	int i = 0;
	t_token		*head = NULL;
	int last_was_word = 0;

	if (is_internal_field_sep(str[0])) {
		i++;
		if (i < len && is_whitespace(str[i]) && is_internal_field_sep(str[i])) {
			while (i < len && is_whitespace(str[i]) && is_internal_field_sep(str[i]))
				i++;
			if (is_internal_field_sep(str[i]))
				i++;
		}
		head = lexer_data_new((t_token){NULL, DELIMITER, NULL});
	}

	while (i < len) {
		int start = i;
		int substrlen = 0;
		while (i < len && !is_internal_field_sep(str[i]))
			i++, substrlen++;

		if (last_was_word)
			lexer_data_append(&head, lexer_data_new((t_token){NULL, DELIMITER, NULL}));
		lexer_data_append(&head, lexer_data_new((t_token){ft_substr(str, start, substrlen), UNQUOTED_WORD, NULL}));
		last_was_word = 1;
		if (i < len && is_internal_field_sep(str[i])) {
			i++;
			while (i < len && is_whitespace(str[i]))
				i++;
		}
	}

	/* debug purposes - inspect tokens 

	t_token t = *head;
	while (t.next) {
		printf(t.type == UNQUOTED_WORD ? "'%s' ->" : "'DELIMITER' -> ", t.value);
		t = *t.next;
	}
	printf(t.type == UNQUOTED_WORD ? "'%s'\n" : "'DELIMITER'\n", t.value);
*/
	return head;
}

void	internal_field_split(t_token **token_ptr, t_token **next_token_ptr)
{
	t_token *new_words;
	t_token	*token;

	token = *token_ptr;
	new_words = do_ifs(token->value);
	if (new_words == NULL || new_words->next == NULL)
		return ;

	// move expander cursor to the last token
	*next_token_ptr = get_last_lexer_data(new_words);

	// put new expanded tokens
	lexer_data_insert(token, new_words);

	// remove legacy token
	t_token **prev = find_token_ptr_before(token_ptr, token);
	remove_token(prev, token_ptr, token);

}
