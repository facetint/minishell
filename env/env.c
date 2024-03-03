/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:05:06 by facetint          #+#    #+#             */
/*   Updated: 2024/03/02 21:38:34 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "../libft/libft.h"
#include "../includes/env.h"
#include <stdlib.h>
#include "../memory-allocator/allocator.h"
#include "../includes/minishell.h"
#include <string.h> //todo lütfen beni sil

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
    key = ft_strdup(key);
    value = ft_strdup(value);
    if (begin)
        return (add_list(key, value, begin));
    else
        return (create_list(key, value));        
}
char *ft_strcdup(char *str, char c)
{
    char *ret_val;
    int i;
    i = 0;
    while (str[i] && str[i] != c)
        i++;
    ret_val = safe_malloc(sizeof(char) * (i + 1));
    i = 0;
    while (str[i] && str[i] != c)
    {
        ret_val[i] = str[i];
        i++;
    }
    ret_val[i] = '\0';
    return (ret_val);
}
t_envList   *make_list(char **env)
{
    t_envList *begin;
    int i;
    char *key;
    char *value;

    i = 0;
    begin = NULL;
    while (env[i])
    {
        key = ft_strcdup(env[i], '=');
        value = ft_strchr(env[i], '=') + 1;
        begin = push_list(key, value, begin);
        i++;
    }
    return (begin);
}
char **make_arr(t_envList *lst)
{
    int     i;
    int     strsize;
    int     size;
    char    **array;
    t_envList   *temp;
    i = 0;
    size = lstsize(lst);
    array = malloc(sizeof(char *) * (size + 1));
    if (!array)
        return (NULL);
    temp = lst;
    while (i < size)
    {
        strsize = ft_strlen(temp->key) + 1 + ft_strlen(temp->value);
        array[i] = malloc(sizeof(char) * (strsize + 1));
        ft_strlcpy(array[i], temp->key, strsize + 1);
        ft_strlcat(array[i], "=", strsize + 1);
        ft_strlcat(array[i], temp->value, strsize + 1);
        temp = temp->next;
        i++;
    }
    array[i] = NULL;
    return (array);
}

void print_list(t_envList *lst)
{
    t_envList *last = NULL;
    while (lst)
    {
        printf("%s=%s\n", lst->key, lst->value);
        last = lst;
        lst = lst->next;
    }
}

