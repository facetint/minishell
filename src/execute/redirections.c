/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcoskun <hcoskun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 16:01:03 by hcoskun           #+#    #+#             */
/*   Updated: 2024/03/16 16:52:29 by hcoskun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "../../includes/minishell.h"

void create_file(char *file)
{
	int fd;

	fd = open(file, O_CREAT, 0644); //todo - handle error
	close(fd);
}

int open_file(char *file, int append)
{
	if (append)
		return open(file, O_RDWR | O_APPEND);
	return open(file, O_RDWR);
}

t_redirection *get_output_redir(t_command *cmd)
{
	t_redirection *result;
	
	result = NULL;
	while (cmd) 
	{
		if (!(cmd->redirections->flags & INPUT))
			result = cmd->redirections;
		cmd = cmd->next;
	}
	return result;
}

t_redirection *get_input_redir(t_command *cmd)
{
	t_redirection *result;
	
	result = NULL;
	while (cmd) 
	{
		if (cmd->redirections->redirected && cmd->redirections->flags & INPUT)
			result = cmd->redirections;
		cmd = cmd->next;
	}
	return result;
}