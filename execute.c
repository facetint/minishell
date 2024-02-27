/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:34:07 by facetint          #+#    #+#             */
/*   Updated: 2024/02/27 14:40:54 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "unistd.h"
#include "stdio.h"
#include <sys/wait.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "memory-allocator/allocator.h"
#include "includes/env.h"

extern t_envList *envList;

t_command *find_before_cmd(t_command *cmds, t_command *beginCmds)
{
    if (cmds == beginCmds)
        return (NULL);
    while (beginCmds->next != cmds) 
        beginCmds = beginCmds->next;
    return (beginCmds);
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
    ret_val[counter] = NULL;
    while (--counter > 0)
        ret_val[counter] = arr[counter - 1]; 
    ret_val[0] = new;
    return (ret_val);
}

char *find_path(char *cmd)
{
    char *path;
    char **path_arr;
    char *joined_path;
    char *new_joined_path;
    int counter;

    path = getenv("PATH");
    path_arr = ft_split(path, ':');

    counter = 0;
    while (path_arr[counter])
    {
        joined_path = ft_strjoin(path_arr[counter], "/");
        new_joined_path = ft_strjoin(joined_path, cmd);
        safe_free(joined_path);
        if (access(new_joined_path, F_OK) == 0)
        {
            safe_free(path_arr);
            return (new_joined_path);
        }
        counter++;
    }
    return (NULL);
}

int isbuiltin(char *cmd)
{
    if (ft_strncmp(cmd, "echo", ft_strlen("echo")) == 0)
        return (1);
    if (ft_strncmp(cmd, "export", ft_strlen("export")) == 0)
        return (1);
    if (ft_strncmp(cmd, "env", ft_strlen("env")) == 0)
        return(1);
    if (ft_strncmp(cmd, "pwd", ft_strlen("pwd")) == 0)
        return (1);
    if (ft_strncmp(cmd, "cd", ft_strlen("cd")) == 0)
        return(1);
    if (ft_strncmp(cmd, "unset", ft_strlen("unset")) == 0)
        return(1);
    return (0);
}
void execute(t_command *cmds, t_command *beginCmds)
{
    int fd[2];
    int pid;
    char *path_cmd;
    char buff[512];
    int rd_bytes;
    char **arg;
    t_command *before;
    int builtin;

    builtin = isbuiltin(cmds->name);

    //echo builtin
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
        if (pid == 0) // child process
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
    }
    else
    {
        if (ft_strncmp(cmds->name, "echo", ft_strlen("echo")) == 0)
        {
            write(fd[1], cmds->args[0], ft_strlen(cmds->args[0]));
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
        else if (ft_strncmp(cmds->name, "env", ft_strlen("env")) == 0)
            print_list(envList);
    }

    close(fd[1]);
    if (before)
       close(before->fd);

    if (cmds->next)
        cmds->fd = fd[0];
    else
    { 
        rd_bytes = read(fd[0], buff, 512);
        close(fd[0]);
        buff[rd_bytes] = 0;
        write(1, buff, rd_bytes);
        printf("\n");
    }
    if (cmds->next)
        execute(cmds->next, beginCmds);
}
