/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_classification.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 09:28:32 by hamza             #+#    #+#             */
/*   Updated: 2024/03/31 09:29:21 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHAR_CLASSIFICATION_H
# define CHAR_CLASSIFICATION_H

typedef enum s_quote
{
	DOUBLE_QUOTE = '\"',
	SINGLE_QUOTE = '\''
}	t_quote;

int	is_meta_char(char c);
int	is_whitespace(char c);
int	is_quote(char c);
int	is_unquoted_word_char(char c);
int	is_name_char(char c);

#endif