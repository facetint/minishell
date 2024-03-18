/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:18:28 by facetint          #+#    #+#             */
/*   Updated: 2024/03/14 19:25:24 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/minishell.h"
#include "../includes/utils.h"
#include "../memory-allocator/allocator.h"
#include <stdio.h>

void join_all_composed_words(t_token **cur_token, char **string_ptr)
{
	char *new_name;
	t_token *lexer_data;

	lexer_data = *cur_token;
	if (lexer_data->type == DELIMITER)
		lexer_data = lexer_data->next;
	while (lexer_data && is_word(lexer_data->type))
	{
		new_name = ft_strjoin(*string_ptr, lexer_data->value);
		if (*string_ptr)
			safe_free(*string_ptr);
		*string_ptr = new_name;
		lexer_data = lexer_data->next;
	}
	*cur_token = lexer_data;
}

void argument_state(t_token **cur_token, t_command *cur_cmd)
{
	int arg_index;

	arg_index = str_arr_size(cur_cmd->args);
	join_all_composed_words(cur_token, &cur_cmd->args[arg_index]);
}

t_redirection create_redirection_data(t_token **lexer_data)
{
    t_redirection redirection;

   	redirection = (t_redirection){0};
	if ((*lexer_data)->type == INPUT_REDIRECTION)
		redirection.flags = INPUT;
	else if ((*lexer_data)->type == HEREDOC_REDIRECTION)
		redirection.flags = HEREDOC | INPUT;
	else if ((*lexer_data)->type == APPEND_REDIRECTION)
		redirection.flags = APPEND;
	*lexer_data = (*lexer_data)->next;
	join_all_composed_words(lexer_data, &redirection.redirected);
	return redirection;
}

void operator_state_p(t_token **cur_token, t_command *cur_cmd)
{
	t_token *lexer_data;
	t_redirection redirection;
	int last_index;

	lexer_data = *cur_token;
	if (lexer_data->type == PIPE)
		return;

	last_index = 0;
	while (cur_cmd->redirections[last_index].redirected)
		last_index++;

	redirection = create_redirection_data(&lexer_data);
	cur_cmd->redirections[last_index] = redirection;

	*cur_token = lexer_data;
}

int count_cmd_args(t_token *lexer_data) {
    int arg_count;

	arg_count = 0;
	while (lexer_data && lexer_data->type != PIPE)
	{
		if (is_operator(lexer_data->type))
		{
			while (lexer_data && !is_word(lexer_data->type))
				lexer_data = lexer_data->next;
			if (lexer_data)
				lexer_data = lexer_data->next;
			continue;
		}
		if (lexer_data->type == DELIMITER)
			lexer_data = lexer_data->next;
		if (lexer_data && is_word(lexer_data->type))
		{
		    while (lexer_data && is_word(lexer_data->type))
				lexer_data = lexer_data->next;
			arg_count++;
		}
		if (lexer_data)
		  lexer_data = lexer_data->next;
	}
	return arg_count;
}

int count_cmd_redirections(t_token *lexer_data)
{
	int redirection_count;

	redirection_count = 0;
	while (lexer_data && lexer_data->type != PIPE)
	{
		if (is_operator(lexer_data->type) && lexer_data->type != PIPE)
			redirection_count++;
		lexer_data = lexer_data->next;
	}
	return redirection_count;
}

void init_command(t_token *lexer_data, t_command **command)
{
	int arg_count;
	int redir_count;

	arg_count = count_cmd_args(lexer_data);
	redir_count = count_cmd_redirections(lexer_data);
	(*command) = ft_calloc(1, sizeof(t_command));
	(*command)->args = ft_calloc(arg_count + 1, sizeof(char *));
	(*command)->redirections = ft_calloc(redir_count + 1, sizeof(t_redirection));
}

parser_state decide_next_state(t_token **cur_token)
{
    if (!*cur_token)
         return NULL;
   	if ((*cur_token)->type == DELIMITER)
	   *cur_token = (*cur_token)->next;
	if (is_word((*cur_token)->type))
	   return (parser_state) argument_state;
	else if (is_operator((*cur_token)->type))
	   return (parser_state) operator_state_p;
	return NULL;
}

t_command *parse(t_token *lexer_data)
{
	t_command *cur_cmd;
	parser_state next_state;
	t_command *result;

	t_token *cur_token = lexer_data;
	init_command(lexer_data, &cur_cmd);
	result = cur_cmd;
	while (1)
	{
	    next_state = decide_next_state(&cur_token);
		if (next_state == NULL)
		  break;
		next_state(&cur_token, cur_cmd);
		if (cur_token && cur_token->type == PIPE)
		{
		    cur_token = cur_token->next;
			init_command(cur_token, &cur_cmd->next);
			cur_cmd = cur_cmd->next;
		}
	}
	return result;
}
