#include "parser.h"
#include "utils.h"
#include "libft/libft.h"

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
	result = ft_str_arr_join((char *[]) {head, replacement, tail}, 3);
	free(head);
	free(tail);
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
	char    *str;
	char    *varname;
	char    *new;
	int        result;
	int        varname_len;

	str = *input;
	varname_len = count_len(&str[index + 1], is_name_char2);
	varname = ft_substr(str, index + 1, varname_len);
	new = replace_string(str, index, varname_len, getenv(varname));
	result = (int) ft_strlen(str);
	*input = new;
	free(varname);
	free(str);
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

/**
 * checks is there backslash at the preceding index
 * @param input the input string
 * @param index the index of the char to check
 * @return 1 if there is backslash at the preceding index, 0 otherwise. (if index is 0, return 0.)
 */
int is_escaped(char *input, unsigned int index) {
	if (index == 0)
		return 0;
	return input[index - 1] == '\\';
}

/**
 * detects quoted parts of the input and checks
 * the char at index is in a single-quoted part or not.
 * @param input the input string
 * @param index the index of the char to check
 * @return 1 if the char at index is in a single-quoted part, 0 otherwise
 */
int is_in_single_quote(char *input, int index) {
	unsigned int i = 0;
	int found_char_distance;
	char quote;
	while (i < index)
	{
		if (is_quote(input[i]) && !is_escaped(input, i))
		{
			quote = input[i];
			found_char_distance = find_char(&input[i + 1], quote);
			if (found_char_distance == -1)
				return 0;
			i += found_char_distance + 1;
			if (i + 1 >= index && quote == SINGLE_QUOTE)
				return 1;
		}
		i++;
	}
	return 0;
}
