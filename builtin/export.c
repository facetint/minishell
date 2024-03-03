/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:15:14 by facetint          #+#    #+#             */
/*   Updated: 2024/03/03 16:54:57 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/env.h"
#include <unistd.h>
#include "../libft/libft.h"

void    builtin_export(t_command *cmd, int fd[2])
{
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
