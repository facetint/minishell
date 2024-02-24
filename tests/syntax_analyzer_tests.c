#include <criterion/criterion.h>
#include "../minishell.h"
#include "test.h"

Test(syntax_analyzer, simple_command)
{
	t_token t4 = (t_token) {.value = strdup("thing"), .next = NULL, .type = UNQUOTED_WORD};
	t_token t3 = (t_token) {.value = NULL, .next = &t4, .type = DELIMITER};
	t_token t2 = (t_token) {.value = strdup("something"), .next = &t3, .type = UNQUOTED_WORD};
	t_token t1 = (t_token) {.value = NULL, .next = &t2, .type = DELIMITER};
	t_token t0 = (t_token) {.value = strdup("\"anything\""), .next = &t1, .type = DOUBLE_QUOTED_WORD};

	cr_assert_eq(is_valid(&t0), 1, "Expected valid, but got invalid.");
}

Test(syntax_analyzer, simple_command_with_pipe)
{
	t_token t4 = (t_token) {.value = strdup("thing"), .next = NULL, .type = UNQUOTED_WORD};
	t_token t3 = (t_token) {.value = NULL, .next = &t4, .type = DELIMITER};
	t_token t2 = (t_token) {.value = strdup("something"), .next = &t3, .type = UNQUOTED_WORD};
	t_token t1 = (t_token) {.value = NULL, .next = &t2, .type = DELIMITER};
	t_token t0 = (t_token) {.value = strdup("\"anything\""), .next = &t1, .type = DOUBLE_QUOTED_WORD};
	t_token t5 = (t_token) {.value = NULL, .next = &t0, .type = PIPE};
	t_token t6 = (t_token) {.value = strdup("thing"), .next = &t5, .type = UNQUOTED_WORD};
	t_token t7 = (t_token) {.value = NULL, .next = &t6, .type = DELIMITER};
	t_token t8 = (t_token) {.value = strdup("something"), .next = &t7, .type = UNQUOTED_WORD};
	t_token t9 = (t_token) {.value = NULL, .next = &t8, .type = DELIMITER};
	t_token t10 = (t_token) {.value = strdup("\"anything\""), .next = &t9, .type = DOUBLE_QUOTED_WORD};

	cr_assert_eq(is_valid(&t10), 1, "Expected valid, but got invalid.");
}

Test(syntax_analyzer, unclosed_double_quotes)
{
	t_token t4 = (t_token) {.value = strdup("thing"), .next = NULL, .type = UNQUOTED_WORD};
	t_token t3 = (t_token) {.value = NULL, .next = &t4, .type = DELIMITER};
	t_token t2 = (t_token) {.value = strdup("something"), .next = &t3, .type = UNQUOTED_WORD};
	t_token t1 = (t_token) {.value = NULL, .next = &t2, .type = DELIMITER};
	t_token t0 = (t_token) {.value = strdup("\"anything"), .next = &t1, .type = DOUBLE_QUOTED_WORD};

	cr_assert_eq(is_valid(&t0), 0, "Expected invalid, but got valid.");
}

Test(syntax_analyzer, unclosed_single_quotes)
{
	t_token t4 = (t_token) {.value = strdup("thing"), .next = NULL, .type = UNQUOTED_WORD};
	t_token t3 = (t_token) {.value = NULL, .next = &t4, .type = DELIMITER};
	t_token t2 = (t_token) {.value = strdup("something"), .next = &t3, .type = UNQUOTED_WORD};
	t_token t1 = (t_token) {.value = NULL, .next = &t2, .type = DELIMITER};
	t_token t0 = (t_token) {.value = strdup("'anything"), .next = &t1, .type = SINGLE_QUOTED_WORD};

	cr_assert_eq(is_valid(&t0), 0, "Expected invalid, but got valid.");
}

Test(syntax_analyzer, pipe_only)
{
	t_token t0 = (t_token) {.value = NULL, .next = NULL, .type = PIPE};

	cr_assert_eq(is_valid(&t0), 0, "Expected invalid, but got valid.");
}

Test(syntax_analyzer, pipe_to_nowhere)
{
	t_token t1 = (t_token) {.value = NULL, .next = NULL, .type = PIPE};
	t_token t0 = (t_token) {.value = strdup("anycommand"), .next = &t1, .type = UNQUOTED_WORD};

	cr_assert_eq(is_valid(&t0), 0, "Expected invalid, but got valid.");
}

Test(syntax_analyzer, pipe_to_pipe)
{
	t_token t2 = (t_token) {.value = NULL, .next = NULL, .type = PIPE};
	t_token t1 = (t_token) {.value = NULL, .next = &t2, .type = PIPE};
	t_token t0 = (t_token) {.value = strdup("anycommand"), .next = &t1, .type = UNQUOTED_WORD};

	cr_assert_eq(is_valid(&t0), 0, "Expected invalid, but got valid.");
}

Test(syntax_analyzer, redirection_only)
{
	t_token t0 = (t_token) {.value = NULL, .next = NULL, .type = OUTPUT_REDIRECTION};
	cr_assert_eq(is_valid(&t0), 0, "Expected invalid, but got valid.");

	t0 = (t_token) {.value = NULL, .next = NULL, .type = INPUT_REDIRECTION};
	cr_assert_eq(is_valid(&t0), 0, "Expected invalid, but got valid.");

	t0 = (t_token) {.value = NULL, .next = NULL, .type = APPEND_REDIRECTION};
	cr_assert_eq(is_valid(&t0), 0, "Expected invalid, but got valid.");

	t0 = (t_token) {.value = NULL, .next = NULL, .type = HEREDOC_REDIRECTION};
	cr_assert_eq(is_valid(&t0), 0, "Expected invalid, but got valid.");
}

Test(syntax_analyzer, redirection_to_nowhere)
{
	t_token t1 = (t_token) {.value = NULL, .next = NULL, .type = OUTPUT_REDIRECTION};
	t_token t0 = (t_token) {.value = strdup("anycommand"), .next = &t1, .type = UNQUOTED_WORD};

	cr_assert_eq(is_valid(&t0), 0, "Expected invalid, but got valid.");
}

Test(syntax_analyzer, redirection_to_redirection)
{
	t_token t2 = (t_token) {.value = NULL, .next = NULL, .type = OUTPUT_REDIRECTION};
	t_token t1 = (t_token) {.value = NULL, .next = &t2, .type = OUTPUT_REDIRECTION};
	t_token t0 = (t_token) {.value = strdup("anycommand"), .next = &t1, .type = UNQUOTED_WORD};

	cr_assert_eq(is_valid(&t0), 0, "Expected invalid, but got valid.");
}

Test(syntax_analyzer, redirection_to_pipe)
{
	t_token t2 = (t_token) {.value = NULL, .next = NULL, .type = PIPE};
	t_token t1 = (t_token) {.value = NULL, .next = &t2, .type = OUTPUT_REDIRECTION};
	t_token t0 = (t_token) {.value = strdup("anycommand"), .next = &t1, .type = UNQUOTED_WORD};

	cr_assert_eq(is_valid(&t0), 0, "Expected invalid, but got valid.");
}

Test(syntax_analyzer, pipe_to_redirection)
{
	t_token t2 = (t_token) {.value = NULL, .next = NULL, .type = OUTPUT_REDIRECTION};
	t_token t1 = (t_token) {.value = NULL, .next = &t2, .type = PIPE};
	t_token t0 = (t_token) {.value = strdup("anycommand"), .next = &t1, .type = UNQUOTED_WORD};

	cr_assert_eq(is_valid(&t0), 0, "Expected invalid, but got valid.");
}

Test(syntax_analyzer, redirection_normal)
{
	t_token t2 = (t_token) {.value = strdup("anycommand"), .next = NULL, .type = UNQUOTED_WORD};
	t_token t1 = (t_token) {.value = NULL, .next = &t2, .type = OUTPUT_REDIRECTION};
	t_token t0 = (t_token) {.value = strdup("anycommand"), .next = &t1, .type = UNQUOTED_WORD};

	cr_assert_eq(is_valid(&t0), 1, "Expected valid, but got invalid.");
}

Test(syntax_analyzer, redirection_normal2)
{
	t_token t2 = (t_token) {.value = strdup("anycommand"), .next = NULL, .type = UNQUOTED_WORD};
	t_token t1 = (t_token) {.value = NULL, .next = &t2, .type = OUTPUT_REDIRECTION};
	t_token t0 = (t_token) {.value = strdup("\"anycommand\""), .next = &t1, .type = DOUBLE_QUOTED_WORD};

	cr_assert_eq(is_valid(&t0), 1, "Expected valid, but got invalid.");
}

