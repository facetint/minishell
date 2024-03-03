/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcoskun <hcoskun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:builtin/export.c
/*   Created: 2024/03/02 14:15:14 by facetint          #+#    #+#             */
/*   Updated: 2024/03/03 11:39:15 by facetint         ###   ########.fr       */
=======
/*   Created: 2023/07/08 16:18:16 by hcoskun           #+#    #+#             */
/*   Updated: 2023/07/11 14:47:49 by hcoskun          ###   ########.fr       */
>>>>>>> main:libft/ft_lstadd_back.c
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/env.h"
#include <unistd.h>
#include "../libft/libft.h"

void    builtin_export(t_command *cmd, int fd[2])
{
<<<<<<< HEAD:builtin/export.c
    (void)cmd;
    t_envList *tmp = get_global_env();
    while (tmp)
    {
        write(fd[1], "declare -x ", 12);
        write(fd[1], tmp->key, ft_strlen(tmp->key));
        write(fd[1], "=", 1);
        write(fd[1], tmp->value, ft_strlen(tmp->value));
        write(fd[1], "\n", 1);
        tmp = tmp->next;
    }

}
=======
	t_list	*last_node;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last_node = ft_lstlast(*lst);
	if (!last_node)
		return ;
	last_node -> next = new;
}
>>>>>>> main:libft/ft_lstadd_back.c
