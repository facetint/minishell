/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcoskun <hcoskun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 20:41:33 by hcoskun42         #+#    #+#             */
/*   Updated: 2023/07/08 18:20:11 by hcoskun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	if (!str[0] && !c)
		return ((char *) str);
	while (str[i])
	{
		if (str[i] == (unsigned char) c)
			return ((char *) str + i);
		i++;
	}
	if ((unsigned char) c)
		return (NULL);
	return ((char *) str + i);
}
