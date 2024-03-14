/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:34:07 by facetint          #+#    #+#             */
/*   Updated: 2024/03/14 19:24:32 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "unistd.h"
#include "stdio.h"
#include <sys/wait.h>
#include <stdlib.h>
#include "../libft/libft.h"
#include "../memory-allocator/allocator.h"
#include "../get_next_line/get_next_line.h"
#include "../includes/env.h"

t_envList	*get_global_env()
{
	static	t_envList env = (t_envList){0};
	return (&env);
}

void	print_and_close(int fd)
{
    char	*line;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		ft_putstr_fd(line, 1);
		safe_free(line);
	}
	close(fd);
}

void    execute_command(t_command *cmd, t_command *before, int fd[2])
{
    char *path_cmd;
    int pid;
    pid = fork();
    if (pid == -1)
        return ft_putstr_fd("Fork error!", 2); //todo exit
    if (pid > 0)
        return; // anne return atıyor.
    path_cmd = find_path(cmd->args[0]);
    if (!path_cmd)
        return ft_putstr_fd("command not found.\n", 2);
    if (before)
    {
        dup2(before->fd, STDIN_FILENO);
        close(before->fd);
    }
    //if (cmd->redirections[0].flags & HEREDOC)
    //    write(0, cmd->redirections[0].redirected, ft_strlen(cmd->redirections[0].redirected));
    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);
    execve(path_cmd, cmd->args, make_arr(get_global_env()));
}
void    execute(t_command *cmds)
{
    handle_command(NULL, cmds, cmds);
}
void writeFd(int fd[2], char *str)
{
    int pid = fork();
    if (pid == -1)
        return ft_putstr_fd("Fork error!", 2);
    if (pid > 0)
        return;
    if (pid == 0)
    {
        close(fd[0]);
        write(fd[1], str, ft_strlen(str));
        close(fd[1]);
        exit(0);
    }
    waitpid(pid, NULL, 0);
}
void    handle_command(t_command *before, t_command *cmd, t_command *first_cmd)
{
    int fd[2];
    if (pipe(fd) == -1)
        return ft_putstr_fd("Pipe error!", 2); //todo exit
    if (cmd->redirections[0].flags & HEREDOC)
    {
        handle_heredocs(cmd);
        if (before)
        {
            read_and_close(before);
            int newfd[2];
            pipe(newfd);
            //writeFd(newfd, buff);
            writeFd(newfd, cmd->redirections[0].redirected);
            write (newfd[1], "\n", 1);
            close(newfd[1]);
            before->fd = newfd[0];
        }
        else
        {
            write(STDOUT_FILENO, cmd->redirections[0].redirected, ft_strlen(cmd->redirections[0].redirected));
            write(STDOUT_FILENO, "\n", 1);
            exit(0);
        }
    }
    if (isbuiltin(cmd->args[0]))
        handle_builtin(cmd, fd);
    else
        execute_command(cmd, before, fd);
    close(fd[1]);
    if (before)
       close(before->fd);
    if (!cmd->next)
        return print_and_close(fd[0]);
    cmd->fd = fd[0];
    handle_command(cmd, cmd->next, first_cmd);
}

