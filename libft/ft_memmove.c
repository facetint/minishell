/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcoskun <hcoskun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 20:36:26 by hcoskun42         #+#    #+#             */
/*   Updated: 2023/07/11 13:22:30 by hcoskun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dest;
	const char	*source;
	int			i;

	if (!dst && !src)
		return ((void *) dst);
	dest = dst;
	source = src;
	if (dest < source)
	{
		ft_memcpy(dest, source, len);
		return (dst);
	}
	i = len - 1;
	while (i >= 0)
	{
		dest[i] = source[i];
		i--;
	}
	return (dst);
}
