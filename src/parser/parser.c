/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:18:28 by facetint          #+#    #+#             */
/*   Updated: 2024/03/29 17:40:32 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../includes/minishell.h"
#include "../../includes/utils.h"
#include "../../memory-allocator/allocator.h"
#include <stdio.h>

void init_command(t_token *lexer_data, t_command **command, t_command *prev)
{
	int arg_count;
	int redir_count;

	arg_count = count_cmd_args(lexer_data);
	redir_count = count_cmd_redirections(lexer_data);
	(*command) = ft_calloc(1, sizeof(t_command));
	(*command)->args = ft_calloc(arg_count + 1, sizeof(char *));
	(*command)->redirections = ft_calloc(redir_count + 1, sizeof(t_redirection));
	(*command)->prev = prev;
}

t_command *parse(t_token *lexer_data)
{
	t_command *cur_cmd;
	parser_state next_state;
	t_command *result;

	t_token *cur_token = lexer_data;
	init_command(lexer_data, &cur_cmd, NULL);
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
			init_command(cur_token, &cur_cmd->next, cur_cmd);
			cur_cmd = cur_cmd->next;
		}
	}
	return result;
}
