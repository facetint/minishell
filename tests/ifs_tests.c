#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../includes/minishell.h"
#include "test.h"

Test(expander, internal_field_split1)
{
	export_env("IFS= \t\n");
	t_token* tokens = do_ifs("a b\nc\td");
	cr_assert_eq(tokens->type, UNQUOTED_WORD);
	cr_assert_str_eq(tokens->value, "a");
	cr_assert_eq(tokens->next->type, DELIMITER);
	cr_assert_eq(tokens->next->next->type, UNQUOTED_WORD);
	cr_assert_str_eq(tokens->next->next->value, "b");
	cr_assert_eq(tokens->next->next->next->type, DELIMITER);
	cr_assert_eq(tokens->next->next->next->next->type, UNQUOTED_WORD);
	cr_assert_str_eq(tokens->next->next->next->next->value, "c");
	cr_assert_eq(tokens->next->next->next->next->next->type, DELIMITER);
	cr_assert_eq(tokens->next->next->next->next->next->next->type, UNQUOTED_WORD);
	cr_assert_str_eq(tokens->next->next->next->next->next->next->value, "d");
	cr_assert_null(tokens->next->next->next->next->next->next->next);
}

Test(expander, internal_field_split2)
{
    export_env("IFS=.");
    t_token *tokens = do_ifs("a.b.c.d");

    cr_assert_eq(tokens->type, UNQUOTED_WORD);
    cr_assert_str_eq(tokens->value, "a");
    cr_assert_eq(tokens->next->type, DELIMITER);
    cr_assert_eq(tokens->next->next->type, UNQUOTED_WORD);
    cr_assert_str_eq(tokens->next->next->value, "b");
    cr_assert_eq(tokens->next->next->next->type, DELIMITER);
    cr_assert_eq(tokens->next->next->next->next->type, UNQUOTED_WORD);
    cr_assert_str_eq(tokens->next->next->next->next->value, "c");
    cr_assert_eq(tokens->next->next->next->next->next->type, DELIMITER);
    cr_assert_eq(tokens->next->next->next->next->next->next->type, UNQUOTED_WORD);
    cr_assert_str_eq(tokens->next->next->next->next->next->next->value, "d");
    cr_assert_null(tokens->next->next->next->next->next->next->next);
}

Test(expander, internal_field_split3)
{
    export_env("IFS=.");
    t_token *tokens = do_ifs("...a..b");

	// DELIMITER -> EMPTY_WORD -> DELIMITER -> EMPTY_WORD ->
	// DELIMITER -> UNQUOTED_WORD -> DELIMITER -> EMPTY_WORD ->
	// DELIMITER -> UNQUOTED_WORD -> DELIMITER
	cr_assert_eq(tokens->type, DELIMITER);
	cr_assert_eq(tokens->next->type, UNQUOTED_WORD);
	cr_assert_str_eq(tokens->next->value, "");
	cr_assert_eq(tokens->next->next->type, DELIMITER);
	cr_assert_eq(tokens->next->next->next->type, UNQUOTED_WORD);
	cr_assert_str_eq(tokens->next->next->next->value, "");
	cr_assert_eq(tokens->next->next->next->next->type, DELIMITER);
	cr_assert_eq(tokens->next->next->next->next->next->type, UNQUOTED_WORD);
	cr_assert_str_eq(tokens->next->next->next->next->next->value, "a");
	cr_assert_eq(tokens->next->next->next->next->next->next->type, DELIMITER);
	cr_assert_eq(tokens->next->next->next->next->next->next->next->type, UNQUOTED_WORD);
	cr_assert_str_eq(tokens->next->next->next->next->next->next->next->value, "");
	cr_assert_eq(tokens->next->next->next->next->next->next->next->next->type, DELIMITER);
	cr_assert_eq(tokens->next->next->next->next->next->next->next->next->next->type, UNQUOTED_WORD);
	cr_assert_str_eq(tokens->next->next->next->next->next->next->next->next->next->value, "b");
	cr_assert_null(tokens->next->next->next->next->next->next->next->next->next->next);
}

Test(expander, internal_field_split4)
{
    export_env("IFS=. ");
    t_token *tokens = do_ifs("   a   b..   c");

	// DELIMITER -> UNQUOTED_WORD -> DELIMITER -> UNQUOTED_WORD ->
	// DELIMITER -> EMPTY_WORD -> DELIMITER -> UNQUOTED_WORD
	cr_assert_eq(tokens->type, DELIMITER);
	cr_assert_eq(tokens->next->type, UNQUOTED_WORD);
	cr_assert_str_eq(tokens->next->value, "a");
	cr_assert_eq(tokens->next->next->type, DELIMITER);
	cr_assert_eq(tokens->next->next->next->type, UNQUOTED_WORD);
	cr_assert_str_eq(tokens->next->next->next->value, "b");
	cr_assert_eq(tokens->next->next->next->next->type, DELIMITER);
	cr_assert_eq(tokens->next->next->next->next->next->type, UNQUOTED_WORD);
	cr_assert_str_eq(tokens->next->next->next->next->next->value, "");
	cr_assert_eq(tokens->next->next->next->next->next->next->type, DELIMITER);
	cr_assert_eq(tokens->next->next->next->next->next->next->next->type, UNQUOTED_WORD);
	cr_assert_str_eq(tokens->next->next->next->next->next->next->next->value, "c");
	cr_assert_null(tokens->next->next->next->next->next->next->next->next);
}

Test(expander, internal_field_split5)
{
	cr_redirect_stdout();
	cr_redirect_stderr();

    export_env("IFS=, ");
    export_env("test=,,,,,");
    handle_input("echo ,,,$test,,,");
	cr_assert_stdout_eq_str(",,,    ,,,\n");
}

