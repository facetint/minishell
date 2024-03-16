/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcoskun <hcoskun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:05:06 by facetint          #+#    #+#             */
/*   Updated: 2024/03/16 14:37:07 by hcoskun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../libft/libft.h"
#include "../../includes/env.h"
#include <stdlib.h>
#include "../../memory-allocator/allocator.h"
#include "../../includes/minishell.h"

t_list  *to_node(char *env)
{
    char		*key;
	char		*value;
	int        eq_index;

    eq_index = ft_strchr(env, '=') - env;
	key = ft_unsafe_substr(env, 0, eq_index);
	value = ft_unsafe_substr(env, eq_index + 1, ft_strlen(env) - eq_index - 1);
	return create_node(key, value);
}

t_list	*to_list(char **env)
{
	t_list	*lst;
	int			i;
	t_list     *node;

	i = 0;
	lst = NULL;
	while (env[i])
	{
	    node = to_node(env[i]);
		if (!node)
		{
            free_list(lst);
            return (NULL);
		}
		ft_lstadd_back(&lst, node);
		i++;
	}
	return (lst);
}

char	**to_arr(t_list *lst)
{
	size_t		i;
	t_list	    *tmp;
	char		**ret_val;
	t_entry    *node;

	i = ft_lstsize(lst);
	ret_val = safe_malloc(sizeof(char *) * (i + 1));
	ret_val[i] = 0;
	tmp = lst;
	i = 0;
	while (tmp)
	{
	    node = tmp->content;
		ret_val[i] = ft_str_arr_join((char*[]) {node->key, "=", node->value}, 3);
		tmp = tmp->next;
		i++;
	}
	return (ret_val);
}

char *find_env(char *key)
{
	t_list *lst;
	t_entry *entry;
	
	lst = get_global_env();
	while (lst)
	{
		entry = lst->content;
		if (ft_strcmp(entry->key, key) == 0)
			return entry->value;
		lst = lst->next;
	}
	return NULL;
}
