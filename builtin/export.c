/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcoskun <hcoskun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:builtin/export.c
/*   Created: 2024/03/02 14:15:14 by facetint          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/03/03 16:54:57 by facetint         ###   ########.fr       */
=======
/*   Updated: 2024/03/03 11:39:15 by facetint         ###   ########.fr       */
=======
/*   Created: 2023/07/08 16:18:16 by hcoskun           #+#    #+#             */
/*   Updated: 2023/07/11 14:47:49 by hcoskun          ###   ########.fr       */
>>>>>>> main:libft/ft_lstadd_back.c
>>>>>>> b447ad4643f5a8bac396730de020e4a38d9fe2be
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
