/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:19:04 by facetint          #+#    #+#             */
/*   Updated: 2024/03/29 22:34:35 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include "../../includes/env.h"

void	builtin_unset(t_command *cmd, int fd[2])
{
	(void)fd;
	unset_env(cmd->args[1]);
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
			free(((t_entry *)cur->content)->key);
			free(((t_entry *)cur->content)->value);
			free(cur->content);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}
