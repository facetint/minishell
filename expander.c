#include "minishell.h"
#include "utils.h"
#include "libft/libft.h"
#include "char_classification.h"
#include "memory-allocator/allocator.h"

/**
 * replaces the string at input with replacement.
 *
 * @param input input string
 * @param p_start start index of the string to replace (placeholder start index)
 * @param p_len length of the string to replace (placeholder length)
 * @param replacement replacement string
 */
char *replace_string(char *input, int p_start, int p_len, char *replacement)
{
	char *head;
	char *tail;
	char *result;

	head = ft_substr(input, 0, p_start);
	tail = ft_substr(input, p_start + p_len + 1, ft_strlen(input) - p_start - p_len);
	if (replacement == NULL)
		result = ft_str_arr_join((char *[]) {head, "", tail}, 3);
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
int expand_variable(char **input, int index)
{
	char	*str;
	char	*varname;
	char	*new;
	int 	result;
	int		varname_len;

	str = *input;
	varname_len = count_len(&str[index + 1], is_a_name_char);
	varname = ft_substr(str, index + 1, varname_len);
	result = (int) ft_strlen(str);
	new = replace_string(str, index, varname_len, getenv(varname));
	*input = new;
	safe_free(varname);
	safe_free(str);
	return index + varname_len + (int) ft_strlen(new) - result;
}

void expand_all_variables(char **string)
{
	int index;
	char *str;

	str = *string;
	index = 0;
	while (str[index])
	{
		if (str[index] == '$')
			index = expand_variable(&str, index);
		index++;
	}
	*string = str;
}



void expand(t_token **head)
{
	t_token *token;

	token = *head;
	while (token)
	{
		/* only unquoted word and double-quoted word tokens are expandable. */
		if (token->type == UNQUOTED_WORD || token->type == DOUBLE_QUOTED_WORD)
		{
			expand_all_variables(&token->value);
			/* only unquoted words are not protected for the split */
			if (token->type == UNQUOTED_WORD)
				internal_field_split(head, token);
		}
		token = token->next;
	}
}

void internal_field_split(t_token **head, t_token *token)
{
	char **new_words;
	int i;
	t_token *list;
	t_token *new;

	new_words = str_split(token->value, is_internal_field_sep);
	if (str_arr_size(new_words) == 1)
		return; /* there is no new word */
	safe_free(token->value);
	token->value = new_words[0];
	list = NULL;
	i = 1; //skip first word
	while (new_words[i])
	{
		new = lexer_data_new((t_token) {.type = DELIMITER});
		lexer_data_append(&list, new);
		new = lexer_data_new((t_token) {.type = UNQUOTED_WORD, .value = new_words[i]});
		lexer_data_append(&list, new);
		i++;
	}
	safe_free(new_words);
	lexer_data_insert(find_pointer_to_next(head, token), list);
}