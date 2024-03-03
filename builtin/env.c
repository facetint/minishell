/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 20:06:35 by facetint          #+#    #+#             */
/*   Updated: 2024/03/02 20:14:21 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"
#include "../includes/env.h"
#include <stdio.h>

void    builtin_env(t_envList *env)
{
    t_envList   *lst;

    lst = env;
    while (lst)
    {
        printf("%s=%s\n", lst->key, lst->value);
        lst = lst->next;
    }
}