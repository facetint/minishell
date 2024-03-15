/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:40:58 by facetint          #+#    #+#             */
/*   Updated: 2024/03/15 03:41:50 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "../../includes/env.h"
#include <stdlib.h>
#include "../../memory-allocator/allocator.h"

char	*strchr_new(const char *s, int c)
{
	while ((char)c != *s)
	{
		if (!*s)
			return (0);
		s++;
	}
	return ((char *)s + 1);
}
char    *strdup_n(char *str, char c)
{
    size_t  i;
    char *ret_val;

    if (!str || str[0] == 0)
        return (0);
    i = 0;
    while (str[i] && str[i] != c)
        i++;
    ret_val = safe_malloc(sizeof(char) * (i + 1));
    ret_val[i] = 0;
    i = 0;
    while (str[i] && str[i] != c)
    {
        ret_val[i] = str[i];
        i++;
    }
    return (ret_val);
}
int lst_size(t_envList *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}
int ft_strcmp(char *s1, char *s2)
{
    if (!s1 || !s2)
        return (1);
	int	counter;

	counter = 0;
	while (s1[counter] && s1[counter] == s2[counter])
		counter++;
	return (s1[counter] - s2[counter]);
}                                                                                                                                                                                                                                                                                                                                                                                                                                   
