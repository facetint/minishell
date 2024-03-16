/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcoskun <hcoskun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:17:46 by facetint          #+#    #+#             */
/*   Updated: 2024/03/16 17:12:08 by hcoskun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <readline/readline.h>
#include "../memory-allocator/allocator.h"
#include <sys/wait.h>
#include <errno.h>
#include "../includes/env.h"

int *get_exit_status()
{
	static int exit_status = 0;
	return(&exit_status);
}


char	*read_heredoc_input(char *eof)
{
	char *line;
	char *input;

	line = NULL;
	input = ft_strdup("");
	while (1)
	{
		line = readline("> ");
		if (signal_type != IN_HEREDOC)
		{
			printf("i caught: '%s'\n", line);
			//handle_input(line);
			return NULL;
		}
		if (!line || ft_strncmp(line, eof, INT_MAX) == 0)
			break;
		if (!*line)
			line = ft_strdup("\n");
		char *new = ft_str_arr_join((char *[]) {input, line, "\n"}, 3);
		safe_free(input);
		input = new;
		safe_free(line);
	}
	return input;
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
    signal_type = IN_HEREDOC;
	int i;

	while (cur)
	{
		i = 0;
		while (cur->redirections[i].redirected)
		{
			if (cur->redirections[i].flags & HEREDOC)
			{
				char *input = read_heredoc_input(cur->redirections[i].redirected);
				if (!input)
				{
					signal_type = DEFAULT;
					return 1;
				}
				safe_free(cur->redirections[i].redirected);
				cur->redirections[i].redirected = input;
			}
			i++;
		}
		cur = cur->next;
	}
	signal_type = DEFAULT;
	return 0;
}

void	handle_invalid_input(t_token *lexical_data)
{
	ft_putstr_fd("\033[91mInvalid input\n\033[39m", 2);
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
	handle_heredocs(parser_data);
	handle_file_redirections(parser_data);

	//debug(lexer_data, parser_data);
	execute(parser_data);
	uninit_tokens(lexer_data);
}

void	handle_memory_error(void)
{
	ft_putstr_fd("Insufficent memory! Minishell aborting...", 2);
	free_list(get_global_env());
	exit(1);
}
