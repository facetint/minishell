/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:18:44 by facetint          #+#    #+#             */
/*   Updated: 2024/03/31 06:18:37 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include "../../libft/libft.h"
#include "../../includes/utils.h"
#include "limits.h"
#include "../../includes/char_classification.h"
#include "../../memory-allocator/allocator.h"

char	*ft_str_arr_join(char **str_list, unsigned int str_count)
{
	unsigned int	total_len;
	unsigned int	result_len;
	unsigned int	i;
	char			*result;

	i = 0;
	total_len = 0;
	if (!str_list)
		return (NULL);
	while (i < str_count)
	{
		total_len += ft_strlen(str_list[i]);
		i++;
	}
	if (total_len == 0)
		return (ft_strdup(""));
	result = (char *)safe_malloc(sizeof(char) * (total_len + 1));
	if (!result)
		return (NULL);
	i = -1;
	result_len = 0;
	while (++i < str_count)
		result_len += ft_strlcpy(&result[result_len], str_list[i], UINT_MAX);
	return (result);
}

char	*get_cur_folder_name(void)
{
	char	*result;
	char	*full_path;
	int		i;

	full_path = getwd(NULL);
	i = (int) ft_strlen(full_path) - 1;
	while (i >= 0 && full_path[i] != '/')
		i--;
	result = ft_strdup(&full_path[i + 1]);
	safe_free(full_path);
	return (result);
}

int	skip_white_spaces(const char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i] && is_whitespace(str[i]))
		i++;
	return (i);
}

int	count_len(const char *str, int (*is_valid)(char))
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i] && is_valid(str[i]))
		i++;
	return (i);
}

int	is_escaped(char *input, unsigned int index)
{
	if (index == 0)
		return (0);
	if (input[index - 1] == '\\')
	{
		if (index >= 2 && input[index - 2] == '\\')
			return (0);
		return (1);
	}
	return (0);
}

int	find_char(const char *str, char looking_for)
{
	int	i;

	if (!str || !*str)
		return (-1);
	i = 0;
	while (str[i] && (str[i] != looking_for || is_escaped((char *)str, i)))
		i++;
	return (i);
}

int	str_arr_size(char **strings)
{
	int	i;

	if (!strings)
		return (-1);
	i = 0;
	while (strings[i])
		i++;
	return (i);
}

int	is_a_name_char(char c)
{
	return (is_name_char(c));
}

int	is_internal_field_sep(char *str, int index)
{
	if (is_escaped(str, index))
		return (0);
	if (is_field_terminator(str[index]))
		return (1);
	return (0);
}

char	*get_prompt(void)
{
	return (ft_str_arr_join((char *[]){ft_itoa(*get_exit_status()), " > "}, 2));
	/*char	*path;
	char	*prompt;
	char	*username;


	path = get_cur_folder_name();
	username = getenv("USER");
	if (username)
		prompt = ft_str_arr_join((char *[]){username, "@", path, "$ "}, 4);
	else
		prompt = ft_str_arr_join((char *[]){path, "$ "}, 2);
	return prompt;*/
}
