/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcoskun <hcoskun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 20:38:47 by hcoskun42         #+#    #+#             */
/*   Updated: 2023/12/31 15:41:09 by hcoskun42        ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../memory-allocator/allocator.h"

static int	wlen(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static int	count_words(char const *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str)
			count++;
		while (*str && *str != c)
			str++;
	}
	return (count);
}

char	**free_all(char **result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		safe_free(result[i]);
		i++;
	}
	safe_free(result);
	return (NULL);
}

char	**ft_split(char const *str, char c)
{
	char	**result;
	int		word_index;
	int		i;
	int		len;

	if (!str)
		return (NULL);
	result = (char **) ft_calloc(sizeof(char *), count_words(str, c) + 1);
	if (!result)
		return (NULL);
	word_index = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (!str[i])
			break ;
		len = wlen(str + i, c);
		result[word_index] = ft_substr(str, i, len);
		if (!result[word_index++])
			return (free_all(result));
		i += len;
	}
	return (result);
}
