/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< Updated upstream:path/libft/ft_strncmp.c
/*   Created: 2023/07/06 17:08:58 by facetint          #+#    #+#             */
/*   Updated: 2023/07/18 14:07:36 by facetint         ###   ########.fr       */
=======
/*   Created: 2023/06/24 21:48:52 by hcoskun42         #+#    #+#             */
/*   Updated: 2024/02/28 16:46:14 by facetint         ###   ########.fr       */
>>>>>>> Stashed changes:libft/ft_strncmp.c
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	if (!s1 && !s2)
		return (0);
	if (!s1 || !s2)
		return (1);
	i = 0;
	while ((s1[i] == s2[i]) && (i < n - 1) && (s1[i] && s2[i]))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
