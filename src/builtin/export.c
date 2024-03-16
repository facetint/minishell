/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcoskun <hcoskun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:01:40 by facetint          #+#    #+#             */
/*   Updated: 2024/03/16 14:15:38 by hcoskun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/env.h"
#include "../../includes/utils.h"
#include <unistd.h>
#include "../../libft/libft.h"

void    builtin_export(t_command *cmd, int fd[2])
{
    t_list *tmp;
    t_entry *node;
	int args_count;
	int i;
	
    (void)cmd;
	args_count = str_arr_size(cmd->args);
	if (args_count == 1)
	{
		tmp = get_global_env();
		while (tmp)
		{
			node = tmp->content;
			ft_putstr_fd("declare -x ", fd[1]);
			ft_putstr_fd(node->key, fd[1]);
			ft_putstr_fd("=", fd[1]);
			ft_putstr_fd(node->value, fd[1]);
			ft_putstr_fd("\n", fd[1]);
			tmp = tmp->next;
		}
		return;
	}

	i = 1;
	while (cmd->args[1]) {
		
	}
}
