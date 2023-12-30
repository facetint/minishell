#include "parser.h"
#include "libft/libft.h"

t_token *unquote(t_token *lexer_data)
{
	char *unquoted_value;
	while (lexer_data)
	{
		if (lexer_data->type == SINGLE_QUOTED_WORD || lexer_data->type == DOUBLE_QUOTED_WORD) {
			unquoted_value = ft_substr(lexer_data->value, 1, ft_strlen(lexer_data->value) - 2);
			free(lexer_data->value);
			lexer_data->value = unquoted_value;
		}
		lexer_data = lexer_data->next;
	}
}