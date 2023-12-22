/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 17:14:02 by facetint          #+#    #+#             */
/*   Updated: 2023/07/09 09:43:00 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		i;
	size_t		src_i;
	size_t		value;

	if (dstsize == 0)
		return (ft_strlen(src));
	else if (dstsize < ft_strlen(dst))
		value = ft_strlen(src) + dstsize;
	else
		value = ft_strlen(src) + ft_strlen(dst);
	i = 0;
	while (dst[i] != '\0')
		i++;
	src_i = 0;
	while (src[src_i] != '\0' && i + 1 < dstsize)
	{
		dst[i] = src[src_i];
		src_i++;
		i++;
	}
	dst[i] = '\0';
	return (value);
}
