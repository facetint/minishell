/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcoskun <hcoskun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 21:51:17 by hcoskun42         #+#    #+#             */
/*   Updated: 2023/07/11 14:41:37 by hcoskun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	contains(char const *set, char const c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

int	find_start(char const *str, char const *set)
{
	int	i;

	i = 0;
	while (str[i] && contains(set, str[i]))
		i++;
	return (i);
}

int	find_end(char const *str, char const *set, int len)
{
	int	i;

	i = (int) len - 1;
	while (i > 0 && contains(set, str[i]))
		i--;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;

	if (!s1)
		return (NULL);
	start = find_start(s1, set);
	end = find_end(s1, set, ft_strlen(s1));
	if (end < start || (!*s1 && !*set))
		return (ft_strdup(""));
	return (ft_substr(s1, start, end - start + 1));
}
