/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 17:34:28 by facetint          #+#    #+#             */
/*   Updated: 2024/04/01 15:43:08 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../includes/minishell.h"
#include "../../includes/utils.h"
#include "../../memory-allocator/allocator.h"

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

t_parser_state	decide_next_state(t_token **cur_token)
{
	if (!*cur_token)
		return (NULL);
	*cur_token = skip_delimiters(*cur_token);
	if (!*cur_token)
		return (NULL);
	if (is_word((*cur_token)->type))
		return ((t_parser_state) argument_state);
	else if (is_operator((*cur_token)->type))
		return ((t_parser_state) operator_state_p);
	return (NULL);
}
