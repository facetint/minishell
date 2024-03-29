/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:01:40 by facetint          #+#    #+#             */
/*   Updated: 2024/03/29 22:51:38 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/env.h"
#include "../../includes/utils.h"
#include <unistd.h>

void	print_exports(t_list *node, int fd[2])
{
	t_entry	*entry;

	while (node)
	{
		entry = node->content;
		ft_putstr_fd("declare -x ", fd[1]);
		ft_putstr_fd(entry->key, fd[1]);
		ft_putstr_fd("=\"", fd[1]);
		ft_putstr_fd(entry->value, fd[1]);
		ft_putstr_fd("\"\n", fd[1]);
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

void	set_export(t_list *env, t_list *node)
{
	t_list	*existing_node;

	existing_node = find_node(env, ((t_entry *)node->content)->key);
	if (!existing_node)
	{
		ft_lstadd_back(&env, node);
		return ;
	}
	free(((t_entry *)existing_node->content)->key);
	free(((t_entry *)existing_node->content)->value);
	free(existing_node->content);
	existing_node->content = node->content;
	free(node);
}

int is_valid_export(char *str)
{
	int i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	i++;
	if (str[i] == '\0')
		return (1);
	if (str[i] != '=')
		return (0);
	i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	builtin_export(t_command *cmd, int fd[2])
{
	t_list	*node;
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
		if (is_valid_export(cmd->args[i])) {
			node = to_node(cmd->args[i]);
			if (!node)
				node = create_node(ft_unsafe_strdup(cmd->args[i]), NULL);

			set_export(*get_global_env(), node);
		} else {
			ft_putstr_fd("minishell: export: `", fd[1]);
			ft_putstr_fd(cmd->args[i], fd[1]);
			ft_putstr_fd("': not a valid identifier\n", fd[1]);
			*get_exit_status() = 1;
		}
		i++;
	}
}
