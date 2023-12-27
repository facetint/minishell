#ifndef UTILS_H
# define UTILS_H

int is_meta_char(char c);
int is_name_char(char c);
int is_whitespace(char c);
int is_quote(char c);
int is_name_char2(char c);

char *get_cur_folder_name(char *full_path);
char *ft_str_join(char **str_list, unsigned int str_count);
int is_equals_ignore_case(char *s1, char *s2, int len);

int skip_white_spaces(const char *str);
int find_char(const char *str, char looking_for);

int count_len(const char *str, int (*is_valid)(char));

#endif
