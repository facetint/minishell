#ifndef UTILS_H
# define UTILS_H

char *get_cur_folder_name();
char *ft_str_arr_join(char **str_list, unsigned int str_count);
int is_a_name_char(char c);
int skip_white_spaces(const char *str);
int find_char(const char *str, char looking_for);
int is_escaped(char *input, unsigned int index);
int is_internal_field_sep(char *str, int index);
char	**str_split(char const *str, int(*is_delimiter)(char *, int));
int count_len(const char *str, int (*is_valid)(char));
int str_arr_size(char **strings);
char	**free_string_arr(char **result);
#endif
