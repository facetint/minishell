#include <criterion/criterion.h>
#include "../minishell.h"
#include "test.h"

Test(unquote, unquote_double_quotes)
{
	t_token t4 = (t_token) {.value = strdup("thing"), .next = NULL, .type = UNQUOTED_WORD};
	t_token t3 = (t_token) {.value = NULL, .next = &t4, .type = DELIMITER};
	t_token t2 = (t_token) {.value = strdup("something"), .next = &t3, .type = UNQUOTED_WORD};
	t_token t1 = (t_token) {.value = NULL, .next = &t2, .type = DELIMITER};
	t_token t0 = (t_token) {.value = strdup("\"anything\""), .next = &t1, .type = DOUBLE_QUOTED_WORD};

	unquote(&t0);
	cr_assert_str_eq(t0.value, "anything");
	cr_assert_str_eq(t2.value, "something");
	cr_assert_str_eq(t4.value, "thing");
}

Test(unquote, unquote_single_quotes)
{
	t_token t4 = (t_token) {.value = strdup("thing"), .next = NULL, .type = UNQUOTED_WORD};
	t_token t3 = (t_token) {.value = NULL, .next = &t4, .type = DELIMITER};
	t_token t2 = (t_token) {.value = strdup("something"), .next = &t3, .type = UNQUOTED_WORD};
	t_token t1 = (t_token) {.value = NULL, .next = &t2, .type = DELIMITER};
	t_token t0 = (t_token) {.value = strdup("'anything'"), .next = &t1, .type = SINGLE_QUOTED_WORD};

	unquote(&t0);
	cr_assert_str_eq(t0.value, "anything");
	cr_assert_str_eq(t2.value, "something");
	cr_assert_str_eq(t4.value, "thing");
}

Test(unquote, unquote_backslash)
{
	t_token t4 = (t_token) {.value = strdup("thing"), .next = NULL, .type = UNQUOTED_WORD};
	t_token t3 = (t_token) {.value = NULL, .next = &t4, .type = DELIMITER};
	t_token t2 = (t_token) {.value = strdup("something"), .next = &t3, .type = UNQUOTED_WORD};
	t_token t1 = (t_token) {.value = NULL, .next = &t2, .type = DELIMITER};
	t_token t0 = (t_token) {.value = strdup("any\\thing"), .next = &t1, .type = UNQUOTED_WORD};

	unquote(&t0);
	cr_assert_str_eq(t0.value, "anything");
	cr_assert_str_eq(t2.value, "something");
	cr_assert_str_eq(t4.value, "thing");
}

Test(unquote, unquote_mixed)
{
	t_token t4 = (t_token) {.value = strdup("thing"), .next = NULL, .type = UNQUOTED_WORD};
	t_token t3 = (t_token) {.value = NULL, .next = &t4, .type = DELIMITER};
	t_token t2 = (t_token) {.value = strdup("something"), .next = &t3, .type = UNQUOTED_WORD};
	t_token t1 = (t_token) {.value = NULL, .next = &t2, .type = DELIMITER};
	t_token t0 = (t_token) {.value = strdup("any\\\"thing"), .next = &t1, .type = UNQUOTED_WORD};

	unquote(&t0);
	cr_assert_str_eq(t0.value, "any\"thing");
	cr_assert_str_eq(t2.value, "something");
	cr_assert_str_eq(t4.value, "thing");
}
