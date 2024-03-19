#include "../includes/minishell.h"
#include <criterion/criterion.h>
#include <fcntl.h>
#include <pthread.h>
#include <unistd.h>

#define OUTPUT_BUFFER_SIZE 1024

struct listen_data {
  int fd_copy;
  int fd;
  int *pipe_fd;
};

char *strjoin(char *s1, char *s2) {
  char *string;
  unsigned long size;

  if (!s1 && !s2)
    return (NULL);
  if (!s1)
    return (strdup(s2));
  if (!s2)
    return (strdup(s1));
  size = strlen(s1) + strlen(s2) + 1;
  string = malloc(sizeof(char) * size);
  if (!string)
    return (NULL);
  strlcpy(string, s1, size);
  strlcat(string, s2, size);
  return (string);
}

struct listen_data start_listening(int fd) {
  struct listen_data result = (struct listen_data){0};

  result.fd = fd;
  result.pipe_fd = malloc(sizeof(int) * 2);
  result.fd_copy = dup(result.fd);

  pipe(result.pipe_fd);
  dup2(result.fd, result.fd_copy);
  dup2(result.pipe_fd[1], result.fd);
  return result;
}

char *stop_listening(struct listen_data ld) {
  dup2(ld.fd_copy, ld.fd);
  close(ld.pipe_fd[1]);

  char buffer[OUTPUT_BUFFER_SIZE] = {0};
  char *result = NULL;

  while (1) {
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

char *exec_and_output(char *input, int fd) {
  struct listen_data fd_trash0, fd_trash1; // i know its ugly but i am busy.
  if (fd != 1)
    fd_trash0 = start_listening(1);
  if (fd != 2)
    fd_trash1 = start_listening(2);

  struct listen_data ld = start_listening(fd);
  handle_input(input);
  char *output = stop_listening(ld);
  
  if (fd != 1)
    stop_listening(fd_trash0);
  if (fd != 2)
    stop_listening(fd_trash1);
  return output;
}

void exec_assert_output(char *input, char *expected_output, int fd) {
  char *output = exec_and_output(input, fd);
  cr_assert_str_eq(output, expected_output);
}

void exec_assert_not_output(char *input, char *unexpected_output, int fd) {
  char *output = exec_and_output(input, fd);
  cr_assert_str_neq(output, unexpected_output);
}

void exec_assert_stdout(char *input, char *expected_output) {
  exec_assert_output(input, expected_output, 1);
}

void exec_assert_stderr(char *input, char *expected_output) {
  exec_assert_output(input, expected_output, 2);
}

Test(test_utils, listen_input) {
  struct listen_data ld = start_listening(1);
  write(1, "hello\n", 6);
  char *output = stop_listening(ld);
  cr_assert_str_eq(output, "hello\n");
}

/*
 * ACTUAL TESTS
 */ 

Test(end2end, echo) {
  exec_assert_stdout("echo hello", "hello\n");
  exec_assert_stdout("echo -n hello", "hello");
  exec_assert_stdout("echo -n -n -n hello", "hello");
  exec_assert_stdout("echo a -n hello", "a -n hello\n");
}

Test(end2end, unquoting) {
  exec_assert_stdout("ec\"h\"'o' hell'o'\\ world", "hello world\n");
  exec_assert_stdout("ec\"h\"'o' hell'o'\\world", "helloworld\n");
  exec_assert_stdout("\"e\"'c'h'o' hello", "hello\n");
  exec_assert_stdout("'e''c'h'o' hello", "hello\n");

  exec_assert_not_output("echo \"hello", "hello\n", 2); // error expected.
  exec_assert_not_output("echo 'hello", "hello\n", 2);  // error expected.

  exec_assert_stdout("echo 'hello\\'", "hello\\\n");
}

Test(end2end, overrided_redirection) {
  exec_assert_stdout("echo ABC > __test_file2 > __test_file3", NULL);
  exec_assert_stdout("cat __test_file2", NULL);
  exec_assert_stdout("cat __test_file3", "ABC\n");
}

Test(end2end, execute_w_path) {
  exec_assert_stdout("/bin/echo hello", "hello\n");
  exec_assert_stdout("/////////////////bin///////////echo sa", "hello\n");
  exec_assert_stdout("////////////////bin//////../bin/////echo sa", "hello\n");
}

Test(end2end, environment_variables) {
  exec_assert_stderr("export abc=def", NULL);
  exec_assert_stdout("echo $abc", "def\n");

  exec_assert_stdout("echo $\"abc\"", "abc\n");

  exec_assert_stderr("export abc=\"k l m n o p r\"", NULL);
  exec_assert_stdout("echo $abc", "\n");
}

Test(end2end, pipes) { exec_assert_stdout("echo hello | cat -e", "hello$\n"); }

Test(end2end, write_and_read_file) {
  exec_assert_stderr("echo hello > __test_file0",
                     NULL); // no error expected.
  exec_assert_stdout("cat __test_file0", "hello\n");
  exec_assert_stderr("rm __test_file0", NULL);
}

Test(end2end, append_and_read_file) {
  exec_assert_stderr("echo hello > __test_file1",
                     NULL); // no error expected.
  exec_assert_stderr("echo world >> __test_file1",
                     NULL); // no error expected.
  exec_assert_stdout("cat __test_file1", "hello\nworld\n");
  exec_assert_stderr("rm __test_file1", NULL);
}
