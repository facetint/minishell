/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:05:06 by facetint          #+#    #+#             */
/*   Updated: 2024/02/29 13:52:44 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "../libft/libft.h"
#include "../includes/env.h"
#include <stdlib.h>
#include "../memory-allocator/allocator.h"
#include "../includes/minishell.h"

t_envList *create_list(char *key, char *value)
{
    t_envList *new_list;

    new_list = safe_malloc(sizeof(t_envList));
    new_list->key = key;
    new_list->value = value;
    new_list->next = NULL;

    return (new_list);
}

t_envList *add_list(char *key, char *value, t_envList *begin)
{
    t_envList *tmp;

    tmp = begin;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = safe_malloc(sizeof(t_envList));
    tmp->next->key = key;
    tmp->next->value = value;
    tmp->next->next = NULL;
    return (begin);
}
t_envList *push_list(char *key, char *value, t_envList *begin)
{
    if (begin)
        return (add_list(key, value, begin));
    else
        return (create_list(key, value));        
}
t_envList   *make_list(char **env)
{
    t_envList   *envList;
    size_t      i;
    char        *val;
    char        *key;
    int         eq_index = -1;

    envList = NULL;
    i = 0;
    while (env[i])
    {
        eq_index = ft_strchr(env[i], '=') - env[i];
        if (eq_index <= 0)
            continue;
        key = ft_substr(env[i], 0, eq_index);
        val = ft_substr(env[i], eq_index + 1, ft_strlen(env[i]) - eq_index - 1);
        envList = push_list(key, val, envList);
        i++;
    }
    return (envList);
}
char **make_arr(t_envList *lst)
{
    size_t i;
    t_envList *tmp;
    char **ret_val;
    char *key;

    i = lstsize(lst);
    ret_val = safe_malloc(sizeof(char *) * (i + 1));
    ret_val[i] = 0;

    tmp = lst;
    i = 0;
    while (tmp)
    {
        key = ft_strjoin(tmp->key, "=");
        ret_val[i] = ft_strjoin(key, tmp->value);
        safe_free(key);
        tmp = tmp->next;
        i++;
    }
    return (ret_val);
}
void print_list(t_envList *lst)
{
    printf("girdi");
    while (lst)
    {
        printf("%s", lst->key);
        printf("=");
        printf("%s\n", lst->value);
        lst = lst->next;
    }
}
void print_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}