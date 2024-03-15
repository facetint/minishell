#include <criterion/criterion.h>
#include "../includes/minishell.h"
#include "test.h"

Test(parser, normal_test)
{
	t_token t2 = (t_token) { .type = UNQUOTED_WORD, .value = "sa", .next = NULL };
	t_token t1 = (t_token) { .type = DELIMITER, .next = &t2 };
	t_token t0 = (t_token) { .type = UNQUOTED_WORD, .value = "echo", .next = &t1 };


	t_command *cmd = parse(&t0);
	cr_assert_not_null(cmd);
	cr_assert_str_eq(cmd->args[0], "echo");
	cr_assert_str_eq(cmd->args[1], "sa");
	cr_assert_null(cmd->args[2]);
	cr_assert_null(cmd->redirections[0].redirected);
	cr_assert_eq(cmd->redirections[0].flags, 0);
}

Test(parser, redirection_first_parser_test)
{
	t_token t3 = (t_token) { .type = UNQUOTED_WORD, .value = "cat", .next = NULL };
	t_token t2 = (t_token) { .type = DELIMITER, .value = NULL, .next = &t3 };
	t_token t1 = (t_token) { .type = UNQUOTED_WORD, .value = "infile", .next = &t2 };
	t_token t0 = (t_token) { .type = INPUT_REDIRECTION, .value = NULL, .next = &t1 };

	t_command *cmd = parse(&t0);
	cr_assert_not_null(cmd);
	cr_assert_str_eq(cmd->args[0], "cat");
	cr_assert_str_eq(cmd->redirections[0].redirected, "infile");
	cr_assert_eq(cmd->redirections[0].flags, INPUT);
	cr_assert_null(cmd->redirections[1].redirected);
}


Test(parser, word_concat_parser)
{
	t_token t4 = (t_token) { .type = UNQUOTED_WORD, .value = "sa", .next = NULL };
	t_token t3 = (t_token) { .type = DELIMITER, .next = &t4 };
	t_token t2 = (t_token) { .type = DOUBLE_QUOTED_WORD, .value = "o", .next = &t3 };
	t_token t1 = (t_token) { .type = SINGLE_QUOTED_WORD, .value = "h", .next = &t2 };
	t_token t0 = (t_token) { .type = UNQUOTED_WORD, .value = "ec", .next = &t1 };


	t_command *cmd = parse(&t0);
	cr_assert_not_null(cmd);
	cr_assert_str_eq(cmd->args[0], "echo");
}

