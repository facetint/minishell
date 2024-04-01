/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 09:28:02 by hamza             #+#    #+#             */
/*   Updated: 2024/04/01 08:58:09 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

typedef struct s_token t_token;

char	*get_cur_folder_name(void);
char	*ft_str_arr_join(char **str_list, unsigned int str_count);
int		skip_white_spaces(const char *str);
int		find_char(const char *str, char looking_for);
int		is_escaped(char *input, unsigned int index);
int		is_internal_field_sep(char *str, int index);
char	**str_split(char const *str, int (is_delimiter)(char *, int));
int		count_len(const char *str, int (*is_valid)(char c));
int		str_arr_size(char **strings);
char	**ft_unsafe_strarrdup(char **arr);
int		is_full_of_spaces(const char *str);
t_token	*skip_delimiters(t_token *token);
void	print_error(char *cmd, char *error);

#endif
