#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "libft/libft.h"

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
	int i = ft_strlen(full_path) - 1;
	while (full_path[i] != '/' && i >= 0) {
		i--;
	}
	return &full_path[i + 1];
}