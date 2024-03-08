/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:04:26 by facetint          #+#    #+#             */
/*   Updated: 2024/03/08 17:41:46 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/minishell.h"
#include "../libft/libft.h"
#include "../memory-allocator/allocator.h"
#include "../includes/env.h"


int isbuiltin(char *cmd)
{
    if (ft_strcmp(cmd, "echo") == 0)
        return (1);
    if (ft_strcmp(cmd, "export") == 0)
        return (1);
    if (ft_strcmp(cmd, "env") == 0)
        return(1);
    if (ft_strcmp(cmd, "exit") == 0)
        return (1);
    if (ft_strcmp(cmd, "pwd") == 0)
        return (1);
    if (ft_strcmp(cmd, "cd") == 0)
        return(1);
    if (ft_strcmp(cmd, "unset") == 0)
        return(1);
    return (0);
}
void    handle_builtin(t_command *cmd, int fd[2])
{
    if (ft_strcmp(cmd->name, "echo") == 0)
        builtin_echo(cmd, fd);
    else if (ft_strcmp(cmd->name, "export") == 0)
        builtin_export(cmd, fd);
    else if (ft_strcmp(cmd->name, "env") == 0)
        builtin_env(get_global_env());
    else if (ft_strcmp(cmd->name, "exit") == 0)
        builtin_exit(cmd);
    else if (ft_strcmp(cmd->name, "pwd") == 0)
        builtin_pwd(cmd);
    if (ft_strcmp(cmd->name, "cd") == 0)
        builtin_cd(cmd, cmd);
    if (ft_strcmp(cmd->name, "unset") == 0)
        return;
}
