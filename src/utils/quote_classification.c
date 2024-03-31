/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_classification.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 09:01:11 by hamza             #+#    #+#             */
/*   Updated: 2024/03/31 09:03:13 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/char_classification.h"

/**
 * @brief The manual defines quotes as " and '.
 * (We don't care about backticks(`))
 */
int	is_quote(char c)
{
	return (c == DOUBLE_QUOTE || c == SINGLE_QUOTE);
}

int	is_unquoted_word_char(char c)
{
	return (!is_meta_char(c)
		&& !is_quote(c)
		&& !is_whitespace(c)
		&& c != '\0');
}
