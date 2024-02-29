/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:34:07 by facetint          #+#    #+#             */
/*   Updated: 2024/02/29 13:51:00 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "../libft/libft.h"
#include "../memory-allocator/allocator.h"
#include "../includes/env.h"
#include "../get_next_line/get_next_line.h"

extern t_envList *envList;

t_command *find_before_cmd(t_command *cmds, t_command *beginCmds)
{
    if (cmds == beginCmds)
        return (NULL);
    while (beginCmds->next != cmds) 
        beginCmds = beginCmds->next;
    return (beginCmds);
}

char **new_arr(char *new, char **arr) // new = ls arr = -l
{
    int counter;
    char **ret_val;

    counter = 0;
    while (arr[counter])
        counter++;
    counter += 2;
    ret_val = safe_malloc(sizeof(char  *) * (counter));
    ret_val[counter] = NULL;
    while (--counter > 0)
        ret_val[counter] = arr[counter - 1]; 
    ret_val[0] = new;
    return (ret_val);
}

void execute(t_command *cmds, t_command *beginCmds)
{
    int fd[2];
    int pid;
    char *path_cmd;
    char **arg;
    t_command *before;
    int builtin;
    char *line;

    builtin = isbuiltin(cmds->name);
    if (!builtin)
    {
        path_cmd = find_path(cmds->name);
        if (!path_cmd)
        {
            ft_putstr_fd("command not found: ", 2);
            return ;
        }
        arg = new_arr(cmds->name, cmds->args);
    }
    before = find_before_cmd(cmds, beginCmds);

    if (!before)
    {
        if (cmds->next == NULL)
            before = NULL;
    }
    if (pipe(fd) == -1)
    {
        ft_putstr_fd("Pipe error!", 2);
        return;
    }
    if (!builtin)
    {
        pid = fork();
        if (pid == -1)
        {
            ft_putstr_fd("Fork error!", 2);
            return;
        }
        if (pid == 0)
        {
            if (before)
            {
                dup2(before->fd, STDIN_FILENO);
                close(before->fd);
            }
            close (fd[0]);
            dup2(fd[1], STDOUT_FILENO);
            close (fd[1]);
            execve(path_cmd, arg, NULL);
        }
        waitpid(pid, NULL, 0);
        safe_free(arg);
        close(fd[1]);
    }
    else
    {
        if (ft_strncmp(cmds->name, "echo", ft_strlen("echo")) == 0)
        {
            builtin_echo(cmds);
        }
        else if (ft_strncmp(cmds->name, "export", ft_strlen("export")) == 0)
        {
            t_envList *tmp = envList;
            while (tmp)
            {
                write(fd[1], tmp->key, ft_strlen(tmp->key));
                write(fd[1], "=", 1);
                write(fd[1], tmp->value, ft_strlen(tmp->value));
                write(fd[1], "\n", 1);
                tmp = tmp->next;
            }
        }
        else if (ft_strncmp(cmds->name, "env", ft_strlen("env")) == 0) {
            print_list(envList);
        }
    }
    close(fd[1]);
    if (before)
       close(before->fd);

    if (cmds->next)
        cmds->fd = fd[0];
    else
    {   
        while ((line = get_next_line(fd[0])) != NULL)
        {
            write(1, line, ft_strlen(line));
            safe_free(line);
        }
        close(fd[0]);
    }
    if (cmds->next)
        execute(cmds->next, beginCmds);
}
