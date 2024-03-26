/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:40:58 by facetint          #+#    #+#             */
/*   Updated: 2024/03/26 12:35:36 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "../../includes/env.h"
#include <stdlib.h>
#include "../../memory-allocator/allocator.h"

/*
 * this function is the standard substr function but it does not use safe_malloc.
 */
char	*ft_unsafe_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*result;

	i = len;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s) || len == 0)
	{
	   result = malloc(sizeof(char));
	   result[0] = '\0';
       return (result);
	}
	if (len > ft_strlen(s + start))
		i = ft_strlen(s + start);
	result = (char *) malloc(sizeof(char) * (i + 1));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s + start, i + 1);
	return (result);
}

t_list *create_node(char *key, char *value)
{
    t_entry *node;
   	t_list	*lst;

    node = malloc(sizeof(t_entry));
    if (!node)
        return (NULL);
    node->key = key;
    node->value = value;
	lst = (t_list *) malloc(sizeof(t_list));
	//printf("%p malloced for %s\n", lst, key);
	if (!lst)
		return (NULL);
	lst -> content = node;
	lst -> next = NULL;
	return lst;
}

void    free_list(t_list *lst)
{
    t_entry *env;
    t_list *tmp;

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

void	abort_function()
{
	free_list(*get_global_env());
	free_memory(); 
}

int ft_strcmp(char *s1, char *s2)
{
    if (!s1 || !s2){
        return (1);
    }

	int	counter = 0;
	while (s1[counter] && s1[counter] == s2[counter])
		counter++;
	return (s1[counter] - s2[counter]);
}
