#include <printf.h>
#include "parser.h"
#include "libft/libft.h"
#include "memory-allocator/allocator.h"
#include "utils.h"

int count_escapes(char *str)
{
	unsigned int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (is_escaped(str, i))
			count++;
		i++;
	}
	return count;
}

char *dup_without_backslash(char *str)
{
	char *result;
	unsigned int i;
	unsigned int j;
	int length;

	length = (int) ft_strlen(str) - count_escapes(str);
	result = safe_malloc(length);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\\')
		{
			if (str[i + 1] == '\0')
				break;
			i++;
		}
		result[j++] = str[i++];
	}
	result[j] = '\0';
	return result;
}

void remove_backslashes(t_token *lexer_data)
{
	char *slashless_val;

	if (lexer_data->type == UNQUOTED_WORD || lexer_data->type == DOUBLE_QUOTED_WORD)
	{
		slashless_val = dup_without_backslash(lexer_data->value);
		safe_free(lexer_data->value);
		lexer_data->value = slashless_val;
	}
}

void unquote(t_token *lexer_data)
{
	char *unquoted_value;
	while (lexer_data)
	{
		if (lexer_data->type == SINGLE_QUOTED_WORD || lexer_data->type == DOUBLE_QUOTED_WORD) {
			unquoted_value = ft_substr(lexer_data->value, 1, ft_strlen(lexer_data->value) - 2);
			safe_free(lexer_data->value);
			lexer_data->value = unquoted_value;
		}
		remove_backslashes(lexer_data);
		lexer_data = lexer_data->next;
	}

}
