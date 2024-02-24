/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcoskun <hcoskun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 21:58:36 by hcoskun42         #+#    #+#             */
/*   Updated: 2023/07/11 13:22:02 by hcoskun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*dest;
	const unsigned char	*source;

	dest = dst;
	source = src;
	if (!dest && !source)
		return (dest);
	i = 0;
	while (i < n)
	{
		dest[i] = source[i];
		i++;
	}
	return (dest);
}
