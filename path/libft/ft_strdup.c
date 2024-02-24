/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:57:18 by facetint          #+#    #+#             */
/*   Updated: 2023/07/20 18:46:27 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*ret_val;

	ret_val = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (ret_val == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ret_val[i] = s1[i];
		i++;
	}
	ret_val[i] = '\0';
	return (ret_val);
}
