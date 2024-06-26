/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:05:06 by facetint          #+#    #+#             */
/*   Updated: 2024/04/02 17:35:06 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../includes/env.h"
#include "../../memory-allocator/allocator.h"
#include "../../includes/minishell.h"
#include "../../includes/utils.h"

t_list	*to_node(char *env)
{
	char	*key;
	char	*value;
	int		eq_index;
	char	*eq_ptr;

	eq_ptr = ft_strchr(env, '=');
	if (!eq_ptr)
		return (NULL);
	eq_index = (int)(eq_ptr - env);
	key = ft_substr(env, 0, eq_index);
	value = ft_substr(env, eq_index + 1, ft_strlen(env) - eq_index - 1);
	return (create_node(key, value));
}

t_list	*to_list(char **env)
{
	int		i;
	t_list	*lst;
	t_list	*node;

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

char	**ft_unsafe_strarrdup(char **arr)
{
	int		size;
	char	**result;
	int		i;

	size = str_arr_size(arr);
	i = 0;
	result = malloc(sizeof(char *) * (size + 1));
	while (i < size)
	{
		result[i] = ft_unsafe_strdup(arr[i]);
		i++;
	}
	result[i] = NULL;
	return (result);
}

char	**to_arr(t_list *lst)
{
	size_t	i;
	char	**ret_val;
	t_list	*tmp;
	t_entry	*node;

	if (lst->content == NULL)
	{
		ret_val = ft_calloc(1, sizeof(char *));
		ret_val[0] = NULL;
	}
	i = ft_lstsize(lst);
	ret_val = safe_malloc(sizeof(char *) * (i + 1));
	ret_val[i] = 0;
	tmp = lst;
	i = 0;
	while (tmp)
	{
		node = tmp->content;
		ret_val[i] = ft_str_arr_join((char *[])
			{node->key, "=", node->value}, 3);
		tmp = tmp->next;
		i++;
	}
	return (ret_val);
}

char	*find_env(char *key)
{
	t_list	*lst;
	t_entry	*entry;

	lst = *get_env();
	if (!lst || !lst->content)
		return (NULL);
	while (lst)
	{
		entry = lst->content;
		if (ft_strcmp(entry->key, key) == 0)
			return (entry->value);
		lst = lst->next;
	}
	return (NULL);
}
