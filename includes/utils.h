/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcoskun <hcoskun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 09:28:02 by hamza             #+#    #+#             */
/*   Updated: 2024/03/31 13:54:27 by hcoskun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

char	*get_cur_folder_name(void);
char	*ft_str_arr_join(char **str_list, unsigned int str_count);
int		skip_white_spaces(const char *str);
int		find_char(const char *str, char looking_for);
int		is_escaped(char *input, unsigned int index);
int		is_internal_field_sep(char *str, int index);
char	**str_split(char const *str, int (is_delimiter)(char *, int));
int		count_len(const char *str, int (*is_valid)(char c));
int		str_arr_size(char **strings);

#endif
