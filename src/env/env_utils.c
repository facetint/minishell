/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcoskun <hcoskun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:40:58 by facetint          #+#    #+#             */
/*   Updated: 2024/03/30 15:45:50 by hcoskun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"
#include <stdlib.h>
#include "../../memory-allocator/allocator.h"

t_list	*create_node(char *key, char *value)
{
	t_entry	*node;
	t_list	*lst;

	node = malloc(sizeof(t_entry));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	lst = (t_list *) malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst -> content = node;
	lst -> next = NULL;
	return (lst);
}

void	free_list(t_list *lst)
{
	t_entry	*env;
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		lst = tmp;
		tmp = tmp->next;
		env = lst->content;
		free(env->key);
		free(env->value);
		free(env);
		free(lst);
	}
}

void	abort_function(void)
{
	free_list(*get_global_env());
	free_memory();
}

int	ft_strcmp(char *s1, char *s2)
{
	int	counter;

	if (!s1 || !s2)
		return (1);
	counter = 0;
	while (s1[counter] && s1[counter] == s2[counter])
		counter++;
	return (s1[counter] - s2[counter]);
}
