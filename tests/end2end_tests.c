#include "../includes/minishell.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <fcntl.h>
#include <pthread.h>
#include <unistd.h>


void redirect_all_stdout(void)
{
	export_env("IFS= \t\n");
	cr_redirect_stdout();
	cr_redirect_stderr();
}

void exec_assert_stdout(char *input, char *expected_output) {
	handle_input(input);
	cr_assert_stdout_eq_str(expected_output);
}

void exec_assert_stderr_exist(char *input) {
	handle_input(input);
	cr_assert_stderr_neq_str("");
}

Test(end2end, echo, .init=redirect_all_stdout)
{
	exec_assert_stdout("echo hello", "hello\n");
}

Test(end2end, echo_n, .init=redirect_all_stdout)
{
	exec_assert_stdout("echo -n hello", "hello");
}

Test(end2end, echo_multiple_n, .init=redirect_all_stdout)
{
	exec_assert_stdout("echo -n -n -n hello", "hello");
}

Test(end2end, echo_fake_option, .init=redirect_all_stdout)
{
	exec_assert_stdout("echo a -n hello", "a -n hello\n");
}

Test(end2end, mixed_quotes, .init=redirect_all_stdout)
{
	exec_assert_stdout("ec\"h\"'o' hell'o'\\ world", "hello world\n");
}

Test(end2end, escaping_alphas, .init=redirect_all_stdout)
{
	exec_assert_stdout("ec\"h\"'o' hell'o'\\world", "helloworld\n");
}

Test(end2end, start_with_quotes, .init=redirect_all_stdout)
{
	exec_assert_stdout("\"e\"'c'h'o' hello", "hello\n");
}

Test(end2end, start_with_quotes_and_spaces, .init=redirect_all_stdout)
{
	exec_assert_stdout("'e''c'h'o' hello", "hello\n");
}

Test(end2end, unclosed_quotes, .init=redirect_all_stdout)
{
	exec_assert_stderr_exist("echo \"hello"); // error expected.
}

Test(end2end, unclosed_quotes2, .init=redirect_all_stdout)
{
	exec_assert_stderr_exist("echo 'hello");  // error expected.
}

Test(end2end, escaped_unclosed_quotes, .init=redirect_all_stdout)
{
  exec_assert_stdout("echo 'hello\\'", "hello\\\n");
}

void prepare_envp() {
	handle_input("export abc=def");
	handle_input("export ghi=jkl");
}

Test(end2end, environment_variables, .init=redirect_all_stdout) {
	prepare_envp();
	exec_assert_stdout("echo $abc", "def\n");
}

Test(end2end, environment_variables2, .init=redirect_all_stdout) {
	prepare_envp();
	exec_assert_stdout("echo $\"abc\"", "abc\n");
}

Test(end2end, environment_variables3, .init=redirect_all_stdout)
{
	prepare_envp();
	exec_assert_stdout("echo $abc$ghi", "defjkl\n");
}

Test(end2end, argument_expander, .init=redirect_all_stdout)
{  
	handle_input("export test=\"o a\"");
	exec_assert_stdout("ech$test", "a\n");
}

Test(end2end, expand_quote, .init=redirect_all_stdout)
{  
	handle_input("export test=\"'\"");
	exec_assert_stdout("echo $test", "'\n");
}
