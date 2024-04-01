/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 07:07:07 by hamza             #+#    #+#             */
/*   Updated: 2024/04/01 07:33:22 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/char_classification.h"
#include "../../includes/utils.h"

int	is_full_of_spaces(const char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	while (str[i])
	{
		if (!is_whitespace(str[i]))
			return (0);
		i++;
	}
	return (1);
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
	if (!str[i])
		i--;
	return (i);
}
