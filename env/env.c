/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:40:43 by facetint          #+#    #+#             */
/*   Updated: 2024/02/27 13:04:48 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "../libft/libft.h"
#include "../includes/env.h"
#include <stdlib.h>
#include "../memory-allocator/allocator.h"

t_envList *create_list(char *key, char *value)
{
    t_envList *new_list;

    new_list = safe_malloc(sizeof(t_envList));
    new_list->key = ft_strdup(key);
    new_list->value = ft_strdup(value);
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
    tmp->next->key = ft_strdup(key);
    tmp->next->value = ft_strdup(value);
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

    envList = NULL;
    i = 0;
    while (env[i])
    {
        key = strdup_n(env[i], '=');
        val = strchr_new(env[i], '=');
        envList = push_list(key, val, envList);
        if (key)
        safe_free(key);
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