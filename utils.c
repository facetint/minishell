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

/**
 * @brief counts the length of the string until the first invalid char.
 * @param str the string to count
 * @param is_valid function which returns 1 if the char is valid, 0 otherwise.
 * @return length of the string until the first invalid char. (if str is NULL, return -1)
 */
int count_len(const char *str, int (*is_valid)(char)) {
	int i;

	if (!str)
		return -1;
	i = 0;
	while (str[i] && is_valid(str[i]))
		i++;
	return i;
}

/**
 * @brief check is a char is escaped or not.
 *
 * we just check if there is a backslash before the char but we
 * have to ensure that the backslash is not escaped.
 *
 * @param input the input string
 * @param index the index of the char to check
 * @return 1 if the char is escaped, 0 otherwise.
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

/**
 * @brief finds char in string and return index of char.
 * and ignores escaped chars.
 *
 * it used to get index distance of any searched char.
 * e.g. if we find a quote, and we want to know how many
 * chars we should skip to find the next quote.
 *
 * @return index of char if found, -1 otherwise.
 */
int find_char(const char *str, char looking_for) {
	int i;

	if (!str)
		return -1;
	i = 0;
	while (str[i] && (str[i] != looking_for || is_escaped((char *)str, i)))
		i++;
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

int is_a_name_char(char c) {
	return is_name_char(c);
}

// here is 1000-point question. do you see different behavior than the bash ?
int is_internal_field_sep(char *str, int index) {
	if (is_escaped(str, index))
		return 0;
	if (is_field_terminator(str[index]))
		return 1;
	return 0;
}