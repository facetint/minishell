/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcoskun <hcoskun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 20:34:22 by hcoskun42         #+#    #+#             */
/*   Updated: 2023/07/11 13:23:07 by hcoskun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*mem;
	size_t				i;

	mem = s;
	i = 0;
	while (i < n)
	{
		if (mem[i] == (unsigned char) c)
			return ((void *)s + i);
		i++;
	}
	return (NULL);
}
