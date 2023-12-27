#include "parser.h"
#include <stdlib.h>

t_token *get_last_lexer_data(t_token *token)
{
	if (!token)
		return NULL;
	while (token->next)
		token = token->next;
	return token;
}

t_token *lexer_data_new(t_token token)
{
	t_token *data;

	data = malloc(sizeof(t_token));
	*data = token;
	data->next = NULL;
	return data;
}

void lexer_data_append(t_token **data, t_token *new_data)
{
	t_token *cur_data;

	if (*data == NULL)
	{
		*data = new_data;
		return;
	}
	cur_data = *data;
	while (cur_data->next != NULL)
		cur_data = cur_data->next;
	cur_data->next = new_data;
}
