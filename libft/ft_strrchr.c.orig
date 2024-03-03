/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcoskun <hcoskun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 21:50:27 by hcoskun42         #+#    #+#             */
/*   Updated: 2023/07/08 16:40:12 by hcoskun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = (int) ft_strlen(str);
	while (i >= 0)
	{
		if (str[i] == (unsigned char) c)
			return ((char *) str + i);
		i--;
	}
	if (c)
		return (NULL);
	return ((char *) str + i);
}
