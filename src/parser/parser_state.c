/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 17:34:28 by facetint          #+#    #+#             */
/*   Updated: 2024/03/31 06:15:42 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../includes/minishell.h"
#include "../../includes/utils.h"
#include "../../memory-allocator/allocator.h"
#include <stdio.h>

void	argument_state(t_token **cur_token, t_command *cur_cmd)
{
	int	arg_index;

	arg_index = str_arr_size(cur_cmd->args);
	join_all_composed_words(cur_token, &cur_cmd->args[arg_index]);
}

void	operator_state_p(t_token **cur_token, t_command *cur_cmd)
{
	t_token			*lexer_data;
	t_redirection	redirection;
	int				last_index;

	lexer_data = *cur_token;
	if (lexer_data->type == PIPE)
		return ;
	last_index = 0;
	while (cur_cmd->redirections[last_index].redirected)
		last_index++;
	redirection = create_redirection_data(&lexer_data);
	cur_cmd->redirections[last_index] = redirection;
	*cur_token = lexer_data;
}

parser_state	decide_next_state(t_token **cur_token)
{
	if (!*cur_token)
		return (NULL);
	if ((*cur_token)->type == DELIMITER)
		*cur_token = (*cur_token)->next;
	if (is_word((*cur_token)->type))
		return ((parser_state) argument_state);
	else if (is_operator((*cur_token)->type))
		return ((parser_state) operator_state_p);
	return (NULL);
}
