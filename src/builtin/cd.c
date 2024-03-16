/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 11:48:16 by facetint          #+#    #+#             */
/*   Updated: 2024/03/15 03:01:38 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include "../../memory-allocator/allocator.h"
#include "../../includes/env.h"
#include <stdlib.h>

char    *get_home(t_command *cmd)
{
    (void)cmd;
    t_list   *env;
    t_envList   *node;

    env = get_global_env();
    while (env)
    {
        node = env->content;
        if (!ft_strcmp(node->key, "HOME"))
            return (node->value);
        env = env->next;
    }
    return (NULL);
}

void    change_old(char *str, t_command *cmd)
{
    (void)cmd;
    t_list   *env;
    t_envList   *node;

    env = get_global_env();
    while (env)
    {
        node = env->content;
        if (!ft_strcmp(node->key, "OLDPWD"))
        {
            if (node->value)
              safe_free(node->value);
            node->value = str;
            break;
        }
        env = env->next;
    }
}
void    change_pwd(t_command *data, t_command *cmd)
{
    t_list   *env;
    t_envList   *node;

    env = get_global_env();
    while (env)
    {
        node = env->content;
        if (!ft_strcmp(node->key, "PWD") && (data->args[0] || ft_strcmp(data->args[1], "~") == 0))
        {
            if (node->value)
                free(node->value);
            node->value = get_home(cmd);
        }
        else if (!ft_strcmp(node->key, "PWD"))
        {
            if (node->value)
              safe_free(node->value);
            node->value = safe_malloc(sizeof(char) * 4097);
            getcwd(node->value, 4097);
            if (getcwd(node->value, 4097) == NULL)
            {
                perror("getcwd");
                return;
            }
            break;
        }
        env = env->next;
    }
}
void    execute_cd(char *str, t_command *data, t_command *cmd)
{
    change_old(str, cmd);
    chdir(get_home(cmd));
    change_pwd(data, cmd);
}
void    builtin_cd(t_command *data, t_command *cmd)
{
    char    *str;

    str = safe_malloc(sizeof(char) * 4097);
    getcwd(str, 4097);
    if (getcwd(str, 4097) == NULL)
    {
        perror("getcwd");
        return;
    }
    if (data->args[1] && data->args[0])
    {
        if (chdir(data->args[1]) == 0)
        {
            change_old(str, cmd);
            change_pwd(data, cmd);
        }
        else
        {
            if (str)
                free(str);
            perror("cd");
        }
    }
    else
        execute_cd(str, data, cmd);
}
