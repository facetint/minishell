/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:01:40 by facetint          #+#    #+#             */
/*   Updated: 2024/03/14 16:05:55 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/env.h"
#include <unistd.h>
#include "../../libft/libft.h"

void    builtin_export(t_command *cmd, int fd[2])
{
    t_list *tmp;
    t_envList *node;
    (void)cmd;

    tmp = get_global_env();
    while (tmp)
    {
        node = tmp->content;
        write(fd[1], "declare -x ", 12);
        write(fd[1], node->key, ft_strlen(node->key));
        write(fd[1], "=", 1);
        write(fd[1], node->value, ft_strlen(node->value));
        write(fd[1], "\n", 1);
        tmp = tmp->next;
    }
}
