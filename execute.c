/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:34:07 by facetint          #+#    #+#             */
/*   Updated: 2024/02/17 23:10:47 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "unistd.h"
#include "stdio.h"
#include <sys/wait.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "memory-allocator/allocator.h"

t_command *find_before_cmd(t_command *cmds, t_command *beginCmds)
{
    printf("cmds : %s\n", cmds->name);
    if (cmds == beginCmds)
        return (NULL);

    while (beginCmds->next != cmds)
    {    
        printf("buraya girdi.");
        printf("begincmds : %s\n", beginCmds->name);
        beginCmds = beginCmds->next;
        printf("begincmds next : %s\n", beginCmds->name);
    }
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
void execute(t_command *cmds, t_command *beginCmds)
{
    int fd[2];
    int pid;
    char *path_cmd;
    char buff[512];
    int readed;
    char **arg;
    t_command *before;

    path_cmd = find_path(cmds->name);
    if (!path_cmd)
    {
        ft_putstr_fd("Command not found: ", 2);
        return ;
    }
        
    arg = new_arr(cmds->name, cmds->args);
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
    close(fd[1]);
    safe_free(arg);

    if (before)
       close(before->fd);

    if (cmds->next)
        cmds->fd = fd[0];
    else
    { 
        readed = read(fd[0], buff, 512);
        close(fd[0]);
        buff[readed] = 0;
        write(1, buff, readed);
        printf("\n");
    }
    if (cmds->next)
        execute(cmds->next, beginCmds);
}
