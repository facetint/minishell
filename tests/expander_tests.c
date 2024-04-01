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

Test(expander, insert_words)
{
	char *strings[] = {"a","b","c","d", NULL};
	t_token t0 = (t_token) {.value = strdup("anything"), .next = NULL, .type = UNQUOTED_WORD};
	t_token *token = &t0;
	insert_uword_tokens(&token, strings);

	check_tokens(token, "anything", "UW D UW D UW D UW");
	cr_assert_str_eq(token->value, "a");
	cr_assert_str_eq(token->next->next->value, "b");
	cr_assert_str_eq(token->next->next->next->next->value, "c");
	cr_assert_str_eq(token->next->next->next->next->next->next->value, "d");
}

Test(expander, insert_words_in_middle)
{
	char *strings[] = {"a","b","c","d", NULL};
	t_token t4 = (t_token) {.value = strdup("thing"), .next = NULL, .type = UNQUOTED_WORD};
	t_token t3 = (t_token) {.value = NULL, .next = &t4, .type = DELIMITER};
	t_token t2 = (t_token) {.value = strdup("something"), .next = &t3, .type = UNQUOTED_WORD};
	t_token t1 = (t_token) {.value = NULL, .next = &t2, .type = DELIMITER};
	t_token t0 = (t_token) {.value = strdup("\"anything\""), .next = &t1, .type = DOUBLE_QUOTED_WORD};
	t_token *token = &t2;
	insert_uword_tokens(&token, strings);

	token = &t0;
	check_tokens(token, "\"anything\" something thing", "DW D UW D UW D UW D UW D UW");
	cr_assert_str_eq(token->value, "\"anything\"");
	cr_assert_str_eq(token->next->next->value, "a");
	cr_assert_str_eq(token->next->next->next->next->value, "b");
	cr_assert_str_eq(token->next->next->next->next->next->next->value, "c");
	cr_assert_str_eq(token->next->next->next->next->next->next->next->next->value, "d");
	cr_assert_str_eq(token->next->next->next->next->next->next->next->next->next->next->value, "thing");
}
