/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:19:04 by facetint          #+#    #+#             */
/*   Updated: 2024/03/03 17:58:20 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>
#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include "../../includes/env.h"

void    builtin_unset(t_command *cmd, int fd[2])
{
	t_list *cur;
	t_list *prev;

	(void)fd; //todo will we use it?
	cur = get_global_env();
	prev = NULL;
	while (cur)
	{
		if (ft_strcmp(((t_entry *)cur->content)->key, cmd->args[1]) == 0)
		{
			if (prev) {
				prev->next = cur->next;
			}
			else
			{
				printf("this env could not unset\n"); // fixme
				return;
			}
			free(((t_entry *)cur->content)->key);
			free(((t_entry *)cur->content)->value);
			free(cur->content);
			free(cur);
			return;
		}
		prev = cur;
		cur = cur->next;
	}
}