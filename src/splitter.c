/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcoskun <hcoskun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:18:32 by facetint          #+#    #+#             */
/*   Updated: 2024/03/31 13:53:09 by hcoskun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/utils.h"
#include "../memory-allocator/allocator.h"
#include <stdio.h>

int	wlen(char const *str, int (is_delimiter)(char *, int))
{
	int	i;

	i = 0;
	while (str[i] && !is_delimiter((char *)str, i))
		i++;
	return (i);
}

int	word_count(char const *str, int (is_delimiter)(char *, int))
{
	int	count;
	int	i;

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

char	**single_element_array(char *str)
{
	char	**result;

	result = (char **) ft_calloc(sizeof(char *), 2);
	result[0] = ft_strdup(str);
	return (result);
}

char	**str_split(char const *str, int (is_delimiter)(char *str, int index))
{
	char	**result;
	int		word_index;
	int		i;
	int		len;

	if (!str)
		return (NULL);
	i = word_count(str, is_delimiter);
	if (i == 1)
		return (single_element_array((char *)str));
	result = (char **)ft_calloc(sizeof(char *), i + 1);
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
