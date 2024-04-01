/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:52:07 by facetint          #+#    #+#             */
/*   Updated: 2024/04/01 15:38:29 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include "../../memory-allocator/allocator.h"
#include "../../includes/env.h"
#include <stdlib.h>

void	change_old(char *str)
{
	t_list	*env;
	t_entry	*node;

	env = *get_global_env();
	while (env)
	{
		node = env->content;
		if (!ft_strcmp(node->key, "OLDPWD"))
		{
			safe_free(node->value);
			node->value = str;
			break ;
		}
		env = env->next;
	}
}

void	change_pwd(t_command *cmd)
{
	t_list	*env;
	t_entry	*node;

	env = *get_global_env();
	while (env)
	{
		node = env->content;
		if (!ft_strcmp(node->key, "PWD") && (!cmd->args[1]))
			node->value = ft_unsafe_strdup(find_env("HOME"));
		else if (!ft_strcmp(node->key, "PWD"))
		{
			node->value = getcwd(NULL, 0);
			break ;
		}
		env = env->next;
	}
}

void	execute_cd(char *str, t_command *cmd)
{
	char	*get_home;

	change_old(str);
	chdir(find_env("HOME"));
	perror("chdir");
	get_home = find_env("HOME");
	if (!get_home)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		*get_exit_status() = 1;
		return ;
	}
	change_pwd(cmd);
	*get_exit_status() = 0;
}

void	builtin_cd(t_command *cmd)
{
	char	*str;

	str = getcwd(NULL, 0);
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
