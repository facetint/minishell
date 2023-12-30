#ifndef UTILS_H
# define UTILS_H

int is_meta_char(char c);
int is_name_char(char c);
int is_whitespace(char c);
int is_quote(char c);
int is_name_char2(char c);

char *get_cur_folder_name(char *full_path);
char *ft_str_arr_join(char **str_list, unsigned int str_count);
int is_equals_ignore_case(char *s1, char *s2, int len);

char get_next_non_whitespace(const char *input, int index);
int skip_white_spaces(const char *str);
int find_char(const char *str, char looking_for);

int is_escaped(char *input, unsigned int index);

int is_internal_field_sep(char *str, int index);
char *safe_strjoin(char *str, char *str2);
char	**str_split(char const *str, int(*is_delimiter)(char *, int));

int count_len(const char *str, int (*is_valid)(char));

int str_arr_size(char **strings);
#endif
