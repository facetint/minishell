/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:34:07 by facetint          #+#    #+#             */
/*   Updated: 2024/03/03 23:31:12 by hcoskun42        ###   ########.tr       */
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

t_envList *get_global_env()
{
    static t_envList env = (t_envList){0};
    return (&env);
}

void print_and_close(int fd) {
    char *line;

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

char **new_arr(char *new, char **arr)
{
    int counter;
    char **ret_val;

    counter = 0;
    while (arr[counter])
        counter++;
    counter += 2;
    ret_val = safe_malloc(sizeof(char *) * (counter));
    ret_val[counter - 1] = NULL;
    while (--counter > 0)
        ret_val[counter] = arr[counter - 1];
    ret_val[0] = new;
    return (ret_val);
}

void execute_command(t_command *cmd, t_command *before, int fd[2])
{
    char *path_cmd;
    int pid;

    pid = fork();
    if (pid == -1)
        return ft_putstr_fd("Fork error!", 2); //todo exit
    if (pid > 0)
        return;

    path_cmd = find_path(cmd->name);
    if (!path_cmd)
        return ft_putstr_fd("Command not found.\n", 2);

    if (before)
    {
        dup2(before->fd, STDIN_FILENO);
        close(before->fd);
    }
    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);
    execve(path_cmd, new_arr(cmd->name, cmd->args), make_arr(get_global_env()));
}

void execute(t_command *cmds)
{
    handle_command(NULL, cmds, cmds);
}

void handle_command(t_command *before, t_command *cmd, t_command *first_cmd)
{
    int fd[2];

    if (pipe(fd) == -1)
        return ft_putstr_fd("Pipe error!", 2); //todo exit

    if (isbuiltin(cmd->name))
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
