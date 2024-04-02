/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:19:04 by facetint          #+#    #+#             */
/*   Updated: 2024/04/02 16:06:10 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include "../../includes/env.h"
#include "../../includes/char_classification.h"
#include "../../memory-allocator/allocator.h"

int	is_valid_unset(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	i++;
	while (is_name_char(str[i]))
		i++;
	if (str[i])
		return (0);
	return (1);
}

void	builtin_unset(t_command *cmd, int fd[2])
{
	int	i;

	(void)fd;
	i = 0;
	while (cmd->args[i])
	{
		if (is_valid_unset(cmd->args[i]))
			unset_env(cmd->args[i]);
		else
		{
			ft_putstr_fd("unset: `", 2);
			ft_putstr_fd(cmd->args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			*get_exit_status() = 1;
		}
		i++;
	}
}

void	unset_env(char *varname)
{
	t_list	*cur;
	t_list	*prev;

	cur = *get_global_env();
	prev = NULL;
	while (cur)
	{
		if (ft_strcmp(((t_entry *)cur->content)->key, varname) == 0)
		{
			if (prev)
				prev->next = cur->next;
			else
				*get_global_env() = cur->next;
			safe_free(((t_entry *)cur->content)->key);
			safe_free(((t_entry *)cur->content)->value);
			safe_free(cur->content);
			safe_free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}
