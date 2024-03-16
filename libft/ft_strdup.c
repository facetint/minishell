/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcoskun <hcoskun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 21:40:48 by hcoskun42         #+#    #+#             */
/*   Updated: 2023/12/31 15:41:22 by hcoskun42        ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../memory-allocator/allocator.h"

char	*ft_strdup(const char *str)
{
	char	*res;
	size_t	size;

	size = ft_strlen(str) + 1;
	res = safe_malloc(sizeof(char) * size);
	if (!res)
		return (NULL);
	ft_strlcpy(res, str, size);
	return (res);
}
