#include "parser.h"
#include "utils.h"
#include "libft/libft.h"
#include <stdio.h>

t_token *expand_lexer_data(char *input, t_token *lexer_data)
{
	int index;
	int length;

	while (lexer_data)
	{
		if (lexer_data->type == WORD)
		{
			index = lexer_data->start;
			while (input[index])
			{
				if (input[index] == '$' && !is_in_single_quote(input, index)) {
					length = count_len(&input[index + 1], is_name_char2);
					char *name = ft_substr(input, index + 1, length);
					char *expanded = getenv(name);
					printf("'%s' expanded to '%s'\n", name, expanded);
					index += length;
				}
				index++;
			}
		}
		lexer_data = lexer_data->next;
	}
	return NULL;
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
