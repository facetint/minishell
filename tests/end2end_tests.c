#include <criterion/criterion.h>
#include "../minishell.h"
#include "../libft/libft.h"
#include "test.h"
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>

#define OUTPUT_BUFFER_SIZE 1024

struct listen_data
{
	int fd_copy;
	int fd;
	int *pipe_fd;
};

char	*strjoin(char const *s1, char const *s2)
{
	char	*string;
	int		size;

	if (!s1 && !s2)return (NULL);
	if (!s1) return (strdup(s2));
	if (!s2) return (strdup(s1));
	size = strlen(s1) + strlen(s2) + 1;
	string = malloc(sizeof(char) * size);
	if (!string)
		return (NULL);
	strlcpy(string, s1, size);
	strlcat(string, s2, size);
	return (string);
}

struct listen_data start_listening(int fd)
{
	struct listen_data result = (struct listen_data) {0};

	result.fd = fd;
	result.pipe_fd = malloc(sizeof(int) * 2);
	result.fd_copy = dup(result.fd);

	pipe(result.pipe_fd); // 0 for read, 1 for write
	dup2(result.fd, result.fd_copy);
	dup2(result.pipe_fd[1], result.fd);
	return result;
}

char *stop_listening(struct listen_data ld)
{
	dup2(ld.fd_copy, ld.fd);
	close(ld.pipe_fd[1]);

	char buffer[OUTPUT_BUFFER_SIZE] = {0};
	char *result = NULL;

	while (1)
	{
		int read_bytes = read(ld.pipe_fd[0], buffer, OUTPUT_BUFFER_SIZE);
		if (read_bytes <= 0)
			break;
		char *new = strjoin(result, buffer);
		free(result);
		result = new;
	}
	close(ld.pipe_fd[0]);
	free(ld.pipe_fd);
	return result;
}

Test(test_utils, listen_input)
{
	struct listen_data ld = start_listening(1);
	write(1, "hello\n", 6);
	char *output = stop_listening(ld);
	cr_assert_str_eq(output, "hello\n");
}

Test(end2end, echo_normal)
{
	struct listen_data ld = start_listening(1);
	handle_input("echo hello");
	char *output = stop_listening(ld);
	cr_assert_str_eq(output, "hello\n");
}

Test(end2end, echo_with_n_arg_normal)
{
	struct listen_data ld = start_listening(1);
	handle_input("echo -n hello");
	char *output = stop_listening(ld);
	cr_assert_str_eq(output, "hello");
}

Test(end2end, echo_with_n_arg_duplicated)
{
	struct listen_data ld = start_listening(1);
	handle_input("echo -n -n -n hello");
	char *output = stop_listening(ld);
	cr_assert_str_eq(output, "hello");
}

Test(end2end, echo_with_fake_arg)
{
	struct listen_data ld = start_listening(1);
	handle_input("echo a -n hello");
	char *output = stop_listening(ld);
	cr_assert_str_eq(output, "a -n hello\n");
}



