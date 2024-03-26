/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:18:32 by facetint          #+#    #+#             */
/*   Updated: 2024/03/26 05:55:36 by hamza            ###   ########.fr       */
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

/**
 * @brief a string split function which allows you to specify a delimiter function.
 * to provide advanced splitting.
 *
 * Used for word splitting. See manual: 3.5.7 Word Splitting
 *
 * @param str			string to split
 * @param is_delimiter	function which returns 1 if the char at index is a delimiter
 * @return array of split strings
 */
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
