/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_classification.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 07:08:18 by hamza             #+#    #+#             */
/*   Updated: 2024/03/31 09:04:44 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/char_classification.h"

/**
 * @brief The manual defines meta characters as: "A character that,
 * when unquoted, separates words.". They tell us a word is over and, we
 * should start a new token.
 *
 * And it continues: "A metacharacter is a >space, tab, newline, or
 * one of the following characters:
 * ‘|’, ‘&’, ‘;’, ‘(’, ‘)’, ‘<’, or ‘>’."
 */
int	is_meta_char(char c)
{
	return (c == ' '
		|| c == '\t'
		|| c == '\n'
		|| c == '|'
		|| c == '<'
		|| c == '>');
}

/**
 * @brief The manual does not define whitespaces explicitly.
 * But I think we don't need a definition.
 */
int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

/**
 * @brief The manual defines a 'name' as "A word consisting solely of
 * letters, numbers, and underscores, and beginning with a letter or
 * underscore. Names are used as shell variable and function names.
 * Also referred to as an identifier."
 *
 * But we don't care about the first letter rule. Probably we should
 * not. 
 *
 * In bash, variable names with digits($0,$1...) are reserved for
 * the positional parameters. (See manual: 3.4.1 Positional Parameters)
 * but our implementation does not have positional parameters. In a
 * nutshell we allow variable names with digits. Because of we can. lol.
 *
 */
char	ft_isalnum(char c);

int	is_name_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}
