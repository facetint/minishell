/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:01:40 by facetint          #+#    #+#             */
/*   Updated: 2024/04/01 15:40:13 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/env.h"
#include "../../includes/utils.h"
#include "../../includes/char_classification.h"

void	print_exports(t_list *node, int fd[2])
{
	t_entry	*entry;

	while (node)
	{
		entry = node->content;
		ft_putstr_fd("declare -x ", fd[1]);
		ft_putstr_fd(entry->key, fd[1]);
		if (ft_strcmp(entry->value, ""))
		{
			ft_putstr_fd("=\"", fd[1]);
			ft_putstr_fd(entry->value, fd[1]);
			ft_putstr_fd("\"", fd[1]);
		}
		ft_putstr_fd("\n", fd[1]);
		node = node->next;
	}
}

t_list	*find_node(t_list *env, char *key)
{
	t_list	*tmp;
	t_entry	*entry;

	tmp = env;
	while (tmp)
	{
		entry = tmp->content;
		if (ft_strcmp(entry->key, key) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	is_valid_export(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	i++;
	while (is_name_char(str[i]) && str[i] != '=')
		i++;
	if (str[i] == '=')
		return (1);
	if (str[i])
		return (0);
	return (1);
}

void	builtin_export(t_command *cmd, int fd[2])
{
	int		args_count;
	int		i;

	(void)cmd;
	args_count = str_arr_size(cmd->args);
	if (args_count == 1)
	{
		print_exports(*get_global_env(), fd);
		return ;
	}
	i = 1;
	while (cmd->args[i])
	{
		if (is_valid_export(cmd->args[i]))
			export_env(cmd->args[i]);
		else
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(cmd->args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			*get_exit_status() = 1;
		}
		i++;
	}
}
