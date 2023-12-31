#include <stdlib.h>
#include <stdio.h>
#include "libft/libft.h"
#include "utils.h"
#include "limits.h"
#include "char_classification.h"
#include "memory-allocator/allocator.h"

char *ft_str_arr_join(char **str_list, unsigned int str_count) {
	unsigned int total_len;
	unsigned int result_len;
	unsigned int i;
	char *result;

	i = 0;
	total_len = 0;
	if (!str_list)
		return NULL;
	while (i < str_count)
	{
		total_len += ft_strlen(str_list[i]);
		i++;
	}
	if (total_len == 0)
		return ft_strdup("");
	result = (char *)safe_malloc(sizeof(char) * (total_len + 1));
	if (!result)
		return NULL;
	i = 0;
	result_len = 0;
	while (i < str_count)
	{
		result_len += ft_strlcpy(&result[result_len], str_list[i], UINT_MAX);
		i++;
	}
	return result;
}

char *get_cur_folder_name(char *full_path)
{
	int i = (int) ft_strlen(full_path) - 1;
	while (i >= 0 && full_path[i] != '/')
		i--;
	return &full_path[i + 1];
}

int skip_white_spaces(const char *str) {
	int i;

	if (!str)
		return -1;
	i = 0;
	while (str[i] && is_whitespace(str[i]))
		i++;
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
	if (input[index - 1] == '\\')
	{
		if (index >= 2 && input[index - 2] == '\\')
			return 0;
		return 1;
	}
	return 0;
}

/*
 * finds char in string and return index of char.
 * and ignores escaped chars.
 *
 * it used to get index distance of any searched char.
 * e.g. if we find a quote, and we want to know how many
 * chars we should skip to find the next quote.
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
		if (is_escaped((char *) str, i))
			i++;
		i++;
	}
	if (str[i] == '\0' && looking_for != '\0')
		return -1;
	return i;
}

int str_arr_size(char **strings)
{
	int i;

	if (!strings)
		return -1;
	i = 0;
	while (strings[i])
		i++;
	return i;
}