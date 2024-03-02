/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2024/02/27 19:05:06 by facetint          #+#    #+#             */
/*   Updated: 2024/02/29 13:52:44 by facetint         ###   ########.fr       */
=======
/*   Created: 2024/02/27 12:40:43 by facetint          #+#    #+#             */
/*   Updated: 2024/02/27 13:04:48 by facetint         ###   ########.fr       */
>>>>>>> c579ba1004872f60388bdc319bc02a6143193b28
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "../libft/libft.h"
#include "../includes/env.h"
#include <stdlib.h>
#include "../memory-allocator/allocator.h"
<<<<<<< HEAD
#include "../includes/minishell.h"
=======
>>>>>>> c579ba1004872f60388bdc319bc02a6143193b28

t_envList *create_list(char *key, char *value)
{
    t_envList *new_list;

    new_list = safe_malloc(sizeof(t_envList));
<<<<<<< HEAD
    new_list->key = key;
    new_list->value = value;
=======
    new_list->key = ft_strdup(key);
    new_list->value = ft_strdup(value);
>>>>>>> c579ba1004872f60388bdc319bc02a6143193b28
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
<<<<<<< HEAD
    tmp->next->key = key;
    tmp->next->value = value;
    tmp->next->next = NULL;
    return (begin);
}
=======
    tmp->next->key = ft_strdup(key);
    tmp->next->value = ft_strdup(value);
    tmp->next->next = NULL;
    return (begin);
}

>>>>>>> c579ba1004872f60388bdc319bc02a6143193b28
t_envList *push_list(char *key, char *value, t_envList *begin)
{
    if (begin)
        return (add_list(key, value, begin));
    else
        return (create_list(key, value));        
}
<<<<<<< HEAD
=======

>>>>>>> c579ba1004872f60388bdc319bc02a6143193b28
t_envList   *make_list(char **env)
{
    t_envList   *envList;
    size_t      i;
    char        *val;
    char        *key;
<<<<<<< HEAD
    int         eq_index = -1;
=======
>>>>>>> c579ba1004872f60388bdc319bc02a6143193b28

    envList = NULL;
    i = 0;
    while (env[i])
    {
<<<<<<< HEAD
        eq_index = ft_strchr(env[i], '=') - env[i];
        if (eq_index <= 0)
            continue;
        key = ft_substr(env[i], 0, eq_index);
        val = ft_substr(env[i], eq_index + 1, ft_strlen(env[i]) - eq_index - 1);
        envList = push_list(key, val, envList);
=======
        key = strdup_n(env[i], '=');
        val = strchr_new(env[i], '=');
        envList = push_list(key, val, envList);
        if (key)
        safe_free(key);
>>>>>>> c579ba1004872f60388bdc319bc02a6143193b28
        i++;
    }
    return (envList);
}
<<<<<<< HEAD
=======

>>>>>>> c579ba1004872f60388bdc319bc02a6143193b28
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
<<<<<<< HEAD
void print_list(t_envList *lst)
{
    printf("girdi");
=======

void print_list(t_envList *lst)
{
>>>>>>> c579ba1004872f60388bdc319bc02a6143193b28
    while (lst)
    {
        printf("%s", lst->key);
        printf("=");
        printf("%s\n", lst->value);
        lst = lst->next;
    }
}
<<<<<<< HEAD
=======

>>>>>>> c579ba1004872f60388bdc319bc02a6143193b28
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