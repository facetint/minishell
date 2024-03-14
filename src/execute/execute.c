/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:34:07 by facetint          #+#    #+#             */
/*   Updated: 2024/03/14 16:52:00 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "stdio.h"
#include <sys/wait.h>
#include <stdlib.h>
#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include "../../memory-allocator/allocator.h"
#include "../../get_next_line/get_next_line.h"
#include "../../includes/env.h"

void	print_heredoc(t_command *cmd)
{
    int    i;

    i = 0;
    while (cmd->redirections[i].redirected)
    {
        if (cmd->redirections[i].flags & HEREDOC)
        {
            int new_fd[2];
            pipe(new_fd);            
            write(new_fd[1], cmd->redirections[i].redirected, ft_strlen(cmd->redirections[i].redirected));
            write(new_fd[1], "\n", 1);
            close(new_fd[1]);
            dup2(new_fd[0], STDIN_FILENO);
            close(new_fd[0]);
        }
        i++;
	}
}

void    run_by_type(t_command *cmd, char *path_cmd)
{
    if (cmd->redirections[0].flags & HEREDOC)
        print_heredoc(cmd);
    if (isbuiltin(cmd->args[0]))
    {
        int new_fd[2];
        new_fd[1] = 1;
        handle_builtin(cmd, new_fd);
        exit(0);
    }
    else
    {
        execve(path_cmd, cmd->args, make_arr(get_global_env()));
        exit(127);
    }
}
void	execute_command(t_command *cmd, t_command *prev, int fd[2])
{
	char	*path_cmd;
    int		pid;

    pid = fork();
    if (pid == -1)
        return ft_putstr_fd("Fork error!", 2); //todo exit
    if (pid != 0)
        return ;
    path_cmd = find_path(cmd->args[0]);
    /*
    if (!path_cmd)
    {
        ft_putstr_fd("bash: ", 2);
        ft_putstr_fd(cmd->args[0], 2);
        ft_putstr_fd(": command not found\n", 2);
        exit(127);
    }*/
    if (prev)
    {
        dup2(prev->output, STDIN_FILENO);
        close(prev->output);
    }
    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);
    run_by_type(cmd, path_cmd);
}

void	handle_command(t_command *prev, t_command *cmd)
{
	int	fd[2];

    if (pipe(fd) == -1)
        return ft_putstr_fd("Pipe error!", 2); //todo exit
    execute_command(cmd, prev, fd);
    close(fd[1]);
    if (prev)
       close(prev->output);
    if (!cmd->next)
        return print_and_close(fd[0]);
    cmd->output = fd[0];
}

void	execute(t_command *cmds)
{
	t_command	*cur;
	t_command	*prev;

    cur = cmds;
    prev = NULL;
    while (cur)
    {
        handle_command(prev, cur);
        prev = cur;
        cur = cur->next;
    }
}
