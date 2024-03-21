/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmanurcetintas <fatmanurcetintas@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:17:46 by facetint          #+#    #+#             */
/*   Updated: 2024/03/22 02:16:11 by fatmanurcet      ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"
#include "../libft/libft.h"
#include "../includes/env.h"

int *get_exit_status()
{
	static int exit_status = 0;
	return(&exit_status);
}

void	handle_file_redirections(t_command *cur)
{
	while (cur) 
	{
		if (!(cur->redirections->flags & INPUT))
			create_file(cur->redirections->redirected);
		cur = cur->next;
	}
}
int	handle_heredocs(t_command *cur)
{
	int i;
	int input_fd;

	input_fd = -1;
	while (cur)
	{
		i = 0;
		while (cur->redirections[i].redirected)
		{
			if (cur->redirections[i].flags & HEREDOC)
			{
				if (input_fd != -1)
					close(input_fd);
				input_fd = read_heredoc_input(cur->redirections[i].redirected);
				if (input_fd == -1)
					return 1;
				cur->redirections[i].input_fd = input_fd;
			}
			i++;
		}
		cur = cur->next;
	}
	return 0;
}

void	handle_invalid_input(t_token *lexical_data)
{
	if (lexical_data->next)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token\n" , 2);
 			*get_exit_status() = 258;
		}
	uninit_tokens(lexical_data);
}

void	handle_input(char *input)
{
	t_token *lexer_data;
	t_command *parser_data;

	lexer_data = lex(input); 
	if (!is_valid(lexer_data))
		return handle_invalid_input(lexer_data);
	expand(&lexer_data);
	unquote(lexer_data);
	parser_data = parse(lexer_data);
	if (handle_heredocs(parser_data))
		return;
	handle_file_redirections(parser_data);

	//debug(lexer_data, parser_data);
	signal_type = RUNNING_COMMAND;
	execute(parser_data);
	signal_type = PROMPT;
	uninit_tokens(lexer_data);
}

void	handle_memory_error(void)
{
	ft_putstr_fd("Insufficent memory! Minishell aborting...", 2);
	free_list(get_global_env());
	exit(1);
}
