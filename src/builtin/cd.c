/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcoskun <hcoskun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 11:48:16 by facetint          #+#    #+#             */
/*   Updated: 2024/03/16 14:57:31 by hcoskun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include "../../memory-allocator/allocator.h"
#include "../../includes/env.h"
#include <stdlib.h>

void    change_old(char *str, t_command *cmd)
{
    (void)cmd;
    t_list   *env;
    t_entry   *node;

    env = get_global_env();
    while (env)
    {
        node = env->content;
        if (!ft_strcmp(node->key, "OLDPWD"))
        {
			if (node->value)
				free(node->value);
            node->value = str;
            break;
        }
        env = env->next;
    }
}
void    change_pwd(t_command *data, t_command *cmd)
{
    t_list   *env;
    t_entry   *node;

    env = get_global_env();
    while (env)
    {
        node = env->content;
        if (!ft_strcmp(node->key, "PWD") && (data->args[0] || ft_strcmp(data->args[1], "~") == 0))
        {
			if (node->value)
				free(node->value);
            node->value = find_env("HOME");
        }
        else if (!ft_strcmp(node->key, "PWD"))
        {
			if (node->value)
				free(node->value);
            node->value = malloc(sizeof(char) * 4097); // todo abort if malloc fail
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
    chdir(find_env("HOME"));
	
    change_pwd(data, cmd);
}

void    builtin_cd(t_command *data, t_command *cmd)
{
    char    *str;
	
    str = malloc(sizeof(char) * 4097); // todo abort if malloc fail
    if (getcwd(str, 4097) == NULL)
    {
        perror("getcwd");
        return;
    }

    if (data->args[1])
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
