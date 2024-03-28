/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:17:46 by facetint          #+#    #+#             */
/*   Updated: 2024/03/28 16:06:39 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/minishell.h"
#include "../libft/libft.h"
#include "../includes/env.h"
#include <fcntl.h>
#include <unistd.h>

int *get_exit_status()
{
	static int exit_status = 0;
	return(&exit_status);
}

void	handle_file_redirections(t_command *cur)
{
	int	i;

	while(cur)
	{
		i = 0;
		cur->output = STDOUT_FILENO;
		cur->input = STDIN_FILENO;
		while (cur->redirections[i].redirected)
		{
			if ((cur->redirections[i].flags & HEREDOC))
			{
				if (cur->input != STDIN_FILENO)
					close(cur->input);
				cur->redirections[i].redir_fd = read_heredoc_input(cur->redirections[i].redirected);
				cur->input = cur->redirections[i].redir_fd;
				if (cur->redirections[i].redir_fd == -1)
				{
					ft_putstr_fd("minishell: ", 2);
					perror(cur->redirections[i].redirected);
					*get_exit_status() = 1;
					break;
				}
			}
			else if (cur->redirections[i].flags & INPUT)
			{	
				if (cur->input != STDIN_FILENO)
					close(cur->input);
				cur->redirections[i].redir_fd = open(cur->redirections[i].redirected, O_RDWR, 0644);
				cur->input = cur->redirections[i].redir_fd;
				if (cur->redirections[i].redir_fd == -1)
				{
					ft_putstr_fd("minishell: ", 2);
					perror(cur->redirections[i].redirected);
					*get_exit_status() = 1;
					break;
				}
			}
			else if (cur->redirections->flags & APPEND)
			{
				if (cur->output != STDOUT_FILENO)
					close(cur->output);
				cur->redirections[i].redir_fd = open(cur->redirections[i].redirected, O_CREAT | O_APPEND | O_WRONLY, 0644);
				cur->output = cur->redirections[i].redir_fd;
				if (cur->redirections[i].redir_fd == -1)
				{
					ft_putstr_fd("minishell: ", 2);
					perror(cur->redirections[i].redirected);
					*get_exit_status() = 1;
					break;
				}
			}
			else
			{
				if (cur->output != STDOUT_FILENO)
					close(cur->output);
				cur->redirections[i].redir_fd = open(cur->redirections[i].redirected, O_CREAT | O_WRONLY, 0644);
				cur->output = cur->redirections[i].redir_fd;
				if (cur->redirections[i].redir_fd == -1)
				{
					ft_putstr_fd("minishell: ", 2);
					perror(cur->redirections[i].redirected);
					*get_exit_status() = 1;
					break;
				}
			}
			if (cur->redirections[i].redir_fd < 0)
			{
				ft_putstr_fd("minishell: ", 2);
				perror(cur->redirections[i].redirected);
				break; //todo handle error
			}
			i++;
		}
		cur = cur->next;
	}
}

void	handle_invalid_input(t_token *lexical_data)
{
	if (lexical_data)
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
	handle_file_redirections(parser_data); 
	signal_type = RUNNING_COMMANDS;
	execute(parser_data);
	signal_type = PROMPT;
	uninit_tokens(lexer_data);
}

void	handle_memory_error(void)
{
	ft_putstr_fd("Insufficent memory! Minishell aborting...", 2);
	free_list(*get_global_env());
	exit(1);
}
