/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 11:48:16 by facetint          #+#    #+#             */
/*   Updated: 2024/03/25 14:56:13 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include "../../memory-allocator/allocator.h"
#include "../../includes/env.h"
#include <stdlib.h>

void    change_old(char *str)
{
    t_list   *env;
    t_entry   *node;

    env = *get_global_env();
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

char	*ft_unsafe_strdup(const char *str)
{
	char	*res;
	size_t	size;

	size = ft_strlen(str) + 1;
	res = malloc(sizeof(char) * size);
	if (!res)
		return (NULL);
	ft_strlcpy(res, str, size);
	return (res);
}

void    change_pwd(t_command *cmd)
{
    t_list   *env;
    t_entry   *node;

    env = *get_global_env();
    while (env)
    {
        node = env->content;
        if (!ft_strcmp(node->key, "PWD") && (!cmd->args[1] || ft_strcmp(cmd->args[1], "~") == 0))
        {
			if (node->value)
				free(node->value);
            node->value = ft_unsafe_strdup(find_env("HOME"));
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

void    execute_cd(char *str, t_command *cmd)
{
    char    *get_home;

    change_old(str);
    chdir(find_env("HOME"));
    perror("chdir");
    get_home = find_env("HOME");
    if(!get_home)
    {
        ft_putstr_fd("cd: HOME not set\n", 2);
        *get_exit_status() = 1;
        return;
    }
    change_pwd(cmd);
    *get_exit_status() = 0;
}

void    builtin_cd(t_command *cmd)
{
    char    *str;
	
    str = malloc(sizeof(char) * 4097); // todo abort if malloc fail
    if (getcwd(str, 4097) == NULL)
    {
        perror("getcwd");
        return;
    }
    if (cmd->args[1])
    {
        if (chdir(cmd->args[1]) == 0)
        {
            change_old(str);
            change_pwd(cmd);
            *get_exit_status() = 0;
        }
        else
        {
            if (str)
                free(str);
            *get_exit_status() = 1;
            perror("cd");
        }
    }
    else
        execute_cd(str, cmd);
}
