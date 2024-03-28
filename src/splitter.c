/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:18:32 by facetint          #+#    #+#             */
/*   Updated: 2024/03/28 16:59:30 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/utils.h"
#include "../memory-allocator/allocator.h"

static int	wlen(char const *str, int(*is_delimiter)(char *, int))
{
	int	i;

	i = 0;
	while (str[i] && !is_delimiter((char *)str, i))
		i++;
	return (i);
}

static int	word_count(char const *str, int(*is_delimiter)(char *, int))
{
	int	count;
	int i;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && is_delimiter((char *)str, i))
			i++;
		if (str[i])
			count++;
		while (str[i] && !is_delimiter((char *)str, i))
			i++;
	}
	if (count == 0)
		count = 1;
	return (count);
}

char	**str_split(char const *str, int(*is_delimiter)(char *, int))
{
	char	**result;
	int		word_index;
	int		i;
	int		len;

	if (!str)
		return (NULL);
	i = word_count(str, is_delimiter);
	result = (char **) ft_calloc(sizeof(char *),  i + 1);
	if (!result)
		return (NULL);
	if (i == 1)
	{
		result[0] = ft_strdup(str);
		return (result);
	}
	word_index = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && is_delimiter((char *)str, i))
			i++;
		if (!str[i])
			break ;
		len = wlen(str + i, is_delimiter);
		result[word_index] = ft_substr(str, i, len);
		word_index++;
		i += len;
	}
	return (result);
}
