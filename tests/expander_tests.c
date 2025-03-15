#include <criterion/criterion.h>
#include "../includes/minishell.h"
#include "test.h"

Test(expander, expand_variables)
{
	handle_input("export TEST_VAR=test");
	t_token t0 = (t_token) {.value = strdup("$TEST_VAR"), .type = UNQUOTED_WORD};
	t_token *token = &t0;
 	expand(&token);
	cr_assert_str_eq(token->value, "test");
}

Test(expander, expand_quoted_word)
{
	handle_input("export TEST_VAR=test");
	t_token t0 = (t_token) {.value = strdup("'TEST_VAR'"), .type = SINGLE_QUOTED_WORD, .next = NULL};
	t_token t1 = (t_token) {.value = strdup("$"), .type = UNQUOTED_WORD, .next = &t0};
	t_token *token = &t1;
 	expand(&token);
	cr_assert_str_eq(token->value, "");
	cr_assert_str_eq(token->next->value, "'TEST_VAR'");

	t0 = (t_token) {.value = strdup("\"TEST_VAR\""), .type = DOUBLE_QUOTED_WORD, .next = NULL};
	t1 = (t_token) {.value = strdup("$"), .type = UNQUOTED_WORD, .next = &t0};
	token = &t1;
 	expand(&token);
	cr_assert_str_eq(token->value, "");
	cr_assert_str_eq(token->next->value, "\"TEST_VAR\"");

}

Test(expander, expand_sequence_variables)
{
	handle_input("export ABC=abc");
	handle_input("export DEF=def");

	t_token t0 = (t_token) {.value = strdup("$ABC$DEF"), .type = UNQUOTED_WORD};
	t_token *token = &t0;
 	expand(&token);
	cr_assert_str_eq(token->value, "abcdef");
}

Test(expander, ifs_split)
{
	export_env("IFS= \t\n");
	handle_input("export TEST_VAR='A B C'");
	t_token t0 = (t_token) {.value = strdup("$TEST_VAR"), .type = UNQUOTED_WORD};
	t_token *token = &t0;
 	expand(&token);
	cr_assert_str_eq(token->value, "A");
	cr_assert_eq(token->type, UNQUOTED_WORD);
	cr_assert_eq(token->next->type, DELIMITER);
	cr_assert_str_eq(token->next->next->value, "B");
	cr_assert_eq(token->next->next->type, UNQUOTED_WORD);
	cr_assert_eq(token->next->next->next->type, DELIMITER);
	cr_assert_str_eq(token->next->next->next->next->value, "C");
	cr_assert_eq(token->next->next->next->next->type, UNQUOTED_WORD);

	t0 = (t_token) {.value = strdup("\"$TEST_VAR\""), .type = DOUBLE_QUOTED_WORD};
	token = &t0;
 	expand(&token);
	cr_assert_str_eq(token->value, "\"A B C\"");
	cr_assert_eq(token->type, DOUBLE_QUOTED_WORD);
}

