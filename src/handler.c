/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmanurcetintas <fatmanurcetintas@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:17:46 by facetint          #+#    #+#             */
/*   Updated: 2024/03/30 22:13:20 by fatmanurcet      ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include "../includes/minishell.h"
#include "../libft/libft.h"
#include "../includes/env.h"
#include <fcntl.h>
#include <unistd.h>

int	*get_exit_status(void)
{
	static int	exit_status = 0;

	return (&exit_status);
}

int	is_empty(t_token *token)
{
	if (!token)
		return (1);
	if (token->type == DELIMITER && token->next == NULL)
		return (1);
	return (0);
}

void	handle_input(char *input)
{
	t_token		*lexer_data;
	t_command	*parser_data;

	lexer_data = lex(input);
	if (!is_valid(lexer_data))
		return (handle_invalid_input(lexer_data));
	if (is_empty(lexer_data))
		return ;
	expand(&lexer_data);
	unquote(lexer_data);
	parser_data = parse(lexer_data);
	handle_file_redirections(parser_data);
	g_signal_type = RUNNING_COMMANDS;
	execute(parser_data);
	g_signal_type = PROMPT;
	uninit_tokens(lexer_data);
}
