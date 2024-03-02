<<<<<<< HEAD
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:40:58 by facetint          #+#    #+#             */
/*   Updated: 2024/02/27 12:40:59 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

>>>>>>> c579ba1004872f60388bdc319bc02a6143193b28
#include "stdio.h"
#include "../includes/env.h"
#include <stdlib.h>
#include "../memory-allocator/allocator.h"

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
char *strdup_n(char *str, char c)
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
int	lstsize(t_envList *lst)
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