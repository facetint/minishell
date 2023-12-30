#include "libft/libft.h"
#include "utils.h"

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
	return (count);
}

char	**free_all(char **result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (NULL);
}

int is_internal_field_sep(char *str, int index) {
	if (is_escaped(str, index))
		return 0;
	if (str[index] == ' ' || str[index] == '\t' || str[index] == '\n')
		return 1;
	return 0;
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
	result = (char **) ft_calloc(sizeof(char *), word_count(str, is_delimiter) + 1);
	if (!result)
		return (NULL);
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
		if (!result[word_index++])
			return (free_all(result));
		i += len;
	}
	return (result);
}

