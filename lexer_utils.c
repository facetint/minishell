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

void lexer_data_insert(t_token **data, t_token *new_list) {
	t_token *last;

	if (!data || !new_list)
		return;
	last = get_last_lexer_data(new_list);
	last->next = (*data)->next;
	(*data)->next = new_list;
}

t_token **find_pointer_to_next(t_token **data, t_token *target)
{
	if (!data || !*data || !target)
		return NULL;
	while (*data)
	{
		if (*data == target)
			return data;
		data = &(*data)->next;
	}
	return NULL;
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

void uninit_tokens(t_token *token) {
	t_token *next;

	while (token)
	{
		next = token->next;
		if (is_word(token->type))
			free(token->value);
		free(token);
		token = next;
	}
}