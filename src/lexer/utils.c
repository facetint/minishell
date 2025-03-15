/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:18:44 by facetint          #+#    #+#             */
/*   Updated: 2024/04/01 15:42:48 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include "../../includes/utils.h"
#include "limits.h"
#include "../../includes/char_classification.h"
#include "../../memory-allocator/allocator.h"
#include "../../includes/env.h"

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
	while (++i < str_count && str_list[i])
		result_len += ft_strlcpy(&result[result_len], str_list[i], UINT_MAX);
	return (result);
}

char	*get_cur_folder_name(void)
{
	char	*result;
	char	*full_path;
	int		i;

	full_path = getcwd(NULL, 0);
	if (!full_path)
		return (NULL);
	i = (int) ft_strlen(full_path) - 1;
	while (i >= 0 && full_path[i] != '/')
		i--;
	result = ft_strdup(&full_path[i + 1]);
	safe_free(full_path);
	return (result);
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

int	is_internal_field_sep(char c)
{
	char *ifs = find_env("IFS");
	if (!ifs)
		return (0);
	if (ft_strchr(ifs, c))
		return (1);
	return (0);
}

char	*get_prompt(void)
{
	char	*path;
	char	*prompt;
	char	*username;

	path = get_cur_folder_name();
	if (!path)
		return (ft_strdup("$"));
	username = find_env("USER");
	if (username)
		prompt = ft_str_arr_join((char *[]){username, "@", path, "$ "}, 4);
	else
		prompt = ft_str_arr_join((char *[]){path, "$ "}, 2);
	return (prompt);
}
