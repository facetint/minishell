/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:17:46 by facetint          #+#    #+#             */
/*   Updated: 2024/04/01 15:45:46 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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
	if (are_quotes_valid(lexer_data) == 0)
		return (handle_invalid_input(lexer_data));
	unquote(lexer_data);
	expand(&lexer_data);
	if (!is_valid(lexer_data))
		return (handle_invalid_input(lexer_data));
	parser_data = parse(lexer_data);
	handle_file_redirections(parser_data);
	g_signal_type = RUNNING_COMMANDS;
	uninit_tokens(lexer_data);
	execute(parser_data);
	g_signal_type = PROMPT;
}
