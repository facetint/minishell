#include <stdlib.h>
#include <stdio.h>
#include "libft/libft.h"
#include "utils.h"

int is_equals_ignore_case(char *s1, char *s2, int n) {
	if (!s1 && !s2)
		return 1;
	if (!s1 || !s2)
		return 0;
	while (n != 0 && *s1 && ft_tolower(*s1) == ft_tolower(*s2)) {
		s1++;
		s2++;
		n--;
	}
	return ft_tolower(*s1) == ft_tolower(*s2);
}

char *ft_str_join(char **str_list, unsigned int str_count) {
	unsigned int total_len = 0;
	unsigned int i = 0;
	if (!str_list)
		return NULL;
	while (i < str_count) {
		total_len += ft_strlen(str_list[i]);
		i++;
	}
	char *result = malloc(sizeof(char) * (total_len + 1));
	if (!result)
		return NULL;
	if (total_len == 0) {
		result[0] = '\0';
		return result;
	}
	i = 0;
	unsigned int result_len = 0;
	while (i < str_count) {
		result_len += ft_strlcpy(&result[result_len], str_list[i], 4294967298);
		i++;
	}
	return result;
}

char *get_cur_folder_name(char *full_path) {
	int i = (int) ft_strlen(full_path) - 1;
	while (full_path[i] != '/' && i >= 0) {
		i--;
	}
	return &full_path[i + 1];
}

int skip_white_spaces(const char *str) {
	int i;

	if (!str)
		return -1;
	i = 0;
	while (str[i] && is_whitespace(str[i])) {
		i++;
	}
	return i;
}

int count_len(const char *str, int (*is_valid)(char)) {
	int i;

	if (!str)
		return -1;
	i = 0;
	while (str[i] && is_valid(str[i]))
		i++;
	return i;
}

char get_next_non_whitespace(const char *input, int index) {
	if (!input)
		return '\0';
	while (input[index] && is_whitespace(input[index]))
		index++;
	return input[index];
}

/**
 * checks is there backslash at the preceding index
 * @param input the input string
 * @param index the index of the char to check
 * @return 1 if there is backslash at the preceding index, 0 otherwise. (if index is 0, return 0.)
 */
int is_escaped(char *input, unsigned int index)
{
	if (index == 0)
		return 0;
	return input[index - 1] == '\\';
}

/*
 * finds char in string and return index of char.
 * and ignores escaped chars.
 *
 * if not found, return -1.
 */
int find_char(const char *str, char looking_for) {
	int i;

	if (!str)
		return -1;
	i = 0;
	while (str[i] && str[i] != looking_for)
	{
		if (str[i] == '\\' && str[i + 1] != '\0')
			i++;
		i++;
	}
	if (str[i] == '\0' && looking_for != '\0')
		return -1;
	return i;
}
