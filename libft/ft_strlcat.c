/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcoskun42 <hcoskun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 21:44:11 by hcoskun42         #+#    #+#             */
/*   Updated: 2023/06/24 21:44:50 by hcoskun42        ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	cpy_len;
	size_t	extra;

	cpy_len = 0;
	extra = 0;
	if (!dst && !size)
		return (ft_strlen(src) * sizeof(char));
	while (dst[cpy_len] && cpy_len < size)
		cpy_len++;
	while (src[extra] && (cpy_len + extra + 1) < size)
	{
		dst[cpy_len + extra] = src[extra];
		extra++;
	}
	if (cpy_len < size)
		dst[cpy_len + extra] = 0;
	return ((cpy_len + ft_strlen(src)) * sizeof(char));
}
