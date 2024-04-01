/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_error_message.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 17:18:11 by facetint          #+#    #+#             */
/*   Updated: 2024/03/31 06:44:16 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include "../../includes/utils.h"
#include "../../includes/char_classification.h"
#include "../../memory-allocator/allocator.h"
#include "../../includes/env.h"

void	unexpected_token_error(t_token *token)
{
	if (token == NULL)
		ft_putstr_fd("syntax error occurred, null token found.\n", 2);
	else
		ft_putstr_fd("syntax error. lol.\n", 2);
}

void	handle_invalid_input(t_token *lexical_data)
{
	if (lexical_data)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		*get_exit_status() = 258;
	}
	uninit_tokens(lexical_data);
}

void	handle_memory_error(void)
{
	ft_putstr_fd("Insufficent memory! Minishell aborting...", 2);
	free_list(*get_global_env());
	exit(1);
}
