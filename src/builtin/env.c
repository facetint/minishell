/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 20:06:35 by facetint          #+#    #+#             */
/*   Updated: 2024/03/14 16:06:13 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include "../../includes/env.h"
#include <stdio.h>

void    builtin_env(t_envList *env, int fd[2])
{
    t_envList   *lst;

    lst = env;
    while (lst)
    {
        write(fd[1], lst->key, ft_strlen(lst->key));
        write(fd[1], "=", 1);
        write(fd[1], lst->value, ft_strlen(lst->value));
        write(fd[1], "\n", 1);
        //printf("%s=%s\n", lst->key, lst->value);
        lst = lst->next;
    }
}
