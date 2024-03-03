/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:34:07 by facetint          #+#    #+#             */
/*   Updated: 2024/03/03 11:35:26 by facetint         ###   ########.fr       */
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
    static t_envList env;

    return (&env);
}
t_command *find_before_cmd(t_command *cmds, t_command *beginCmds)
{
    if (cmds == beginCmds)
        return (NULL);
    while (beginCmds->next != cmds) 
        beginCmds = beginCmds->next;
    return (beginCmds);
}

void read_and_print(int fd) {
    char *line;
    while ((line = get_next_line(fd)) != NULL)
    {
        write(1, line, ft_strlen(line));
        safe_free(line);
    }
}

char **new_arr(char *new, char **arr)
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

    builtin = isbuiltin(cmds->name);
    before = find_before_cmd(cmds, beginCmds);
    
    if (pipe(fd) == -1)
        return ft_putstr_fd("Pipe error!", 2);

    if (!builtin)
    {
        pid = fork();
        if (pid == -1)
            return ft_putstr_fd("Fork error!", 2);
        
        path_cmd = find_path(cmds->name);
        if (!path_cmd)
            return ft_putstr_fd("command not found: ", 2);
        arg = new_arr(cmds->name, cmds->args);

        if (pid == 0) //child
        {
            if (before)
            {
                dup2(before->fd, STDIN_FILENO);
                close(before->fd);
            }
            close(fd[0]);
            dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);
            execve(path_cmd, arg, NULL);
        }
        //waitpid(pid, NULL, 0);
        safe_free(arg);
    }
    else
        handle_builtin(cmds, fd);
    close(fd[1]);
    if (before)
       close(before->fd);
    if (cmds->next)
    {
        cmds->fd = fd[0];
        execute(cmds->next, beginCmds);
    }
    else
    {
        read_and_print(fd[0]);
        close(fd[0]);
    }
}
