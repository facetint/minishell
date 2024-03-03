/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcoskun <hcoskun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 21:49:28 by hcoskun42         #+#    #+#             */
/*   Updated: 2023/07/11 13:18:48 by hcoskun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		needle_len;
	size_t		i;

	if (!haystack && !len)
		return (NULL);
	if (*needle == 0)
		return ((char *) haystack);
	needle_len = ft_strlen(needle);
	i = 0;
	while (haystack[i] && i < len && needle_len <= len - i)
	{
		if (ft_strncmp(haystack + i, needle, needle_len) == 0)
			return ((char *) haystack + i);
		i++;
	}
	return (NULL);
}
