#include "libft/libft.h"
#include "parser.h"

t_token *lexer_data_new(t_token token) {
	t_token *data = malloc(sizeof(t_token));
	data->type = token.type;
	data->end = token.end;
	data->next = NULL;
	return data;
}

t_token *lexer_data_append(t_token *data, t_token *new_data) {
	if (data == NULL)
		return new_data;
	t_token *cur_data = data;
	while (cur_data->next != NULL)
		cur_data = cur_data->next;
	cur_data->next = new_data;
	return data;
}

t_token parse(char *input) {

}

int is_meta_char(char c)
{
	return c == '|' || c == '<' || c == '>' ; // c == '&' || c == ';' || c == '(' || c == ')'  
}

int is_name_char(char c)
{
	return ft_isalnum(c) || c == '_';
}

int is_whitespace(char c)
{
	return c == ' ' || c == '\t';
}

int skip_white_spaces(char *str) {
	int i;

	if (!str)
		return -1;
	i = 0;	
	while (*str && is_whitespace(*str))
		i++;
	return i;
}

t_token_type get_meta_token_type(char *input) {
	if (!input && !*input)
		return UNKNOWN;
	if (input[0] == '>') {
		if (input[1] == '>')
			return APPEND_REDIRECTION;
		return OUTPUT_REDIRECTION;
	}
	if (input[0] == '<') {
		if (input[1] == '<')
			return HEREDOC_REDIRECTION;
		return INPUT_REDIRECTION;
	}
	if (input[0] == '|')
		return PIPE;
}

void command_state(t_token *lexer_data, char *input, int index) {
	//assume input and lexer_data is non-null
	//assume 0 < index < strlen(input)
	index += skip_white_spaces(&input[index]);
	if (!input[index])
		return; //do not append new token if command name not found.
	t_token token;
	token.start = index;
	while (input[index] && is_name_char(input))
		index++;
	token.end = index;
	lexer_data = lexer_data_append(lexer_data, lexer_data_new(token));
	command_after_state(lexer_data, input, index);
}

void command_after_state(t_token *lexer_data, char *input, int index) {
	//assume input and lexer_data is non-null
	//assume 0 < index < strlen(input) 
	index += skip_white_spaces(&input[index]);
	if (!input[index])
		return; //do not append new token if command name not found.
	if (is_meta_char(input[index]))
		delimeter_state(lexer_data, input, index);
	else
		argument_state(lexer_data, input, index);
}

void argument_state(t_token *lexer_data, char *input, int index) {
	//assume input and lexer_data is non-null
	//assume 0 < index < strlen(input) 
	//assume input[index] is not a null, whitespace or metacharacter.
	t_token token;
	token.start = index;
	if (input[index] == DOUBLE_QUOTE) {
		index++;
		while (input[index] && input[index] == DOUBLE_QUOTE)
			index++;
	}
	token.end = index;
}

void delimeter_state(t_token *lexer_data, char *input, int index) {
	t_token_type type = get_meta_token_type(&input[index]);

}