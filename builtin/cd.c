/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 11:48:16 by facetint          #+#    #+#             */
/*   Updated: 2024/03/09 01:02:26 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../memory-allocator/allocator.h"
#include "../includes/env.h"

char    *get_home(t_command *cmd)
{
    (void)cmd;
    t_envList   *env;
    
    env = get_global_env();
    while (env)
    {
        if (!ft_strcmp(env->key, "HOME"))
            return (env->value);
        env = env->next;
    }
    return (NULL);
}
void    change_old(char *str, t_command *cmd)
{
    (void)cmd;
    t_envList   *env;
    env = get_global_env();
    while (env)
    {
        if (!ft_strcmp(env->key, "OLDPWD"))
        {
            if (env->value)
              safe_free(env->value);
            env->value = str;
            break;
        }
        env = env->next;
    }
}
void    change_pwd(t_command *data, t_command *cmd)
{
    t_envList   *env;

    env = get_global_env();
    while (env)
    {
        if (!ft_strcmp(env->key, "PWD") && data->args[0])
        {
            if (env->value)
                free(env->value);
            env->value = get_home(cmd);
        }
        else if (!ft_strcmp(env->key, "PWD"))
        {
            if (env->value)
              safe_free(env->value);
            env->value = safe_malloc(sizeof(char) * 4097);
            getcwd(env->value, 4097);
            if (getcwd(env->value, 4097) == NULL)
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
    chdir(get_home(cmd));
    change_old(str, cmd);
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
    if (data->args[0] && data->args)
    {
        if (chdir(data->args[0]) == 0)
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
