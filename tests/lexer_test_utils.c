#include <criterion/criterion.h>
#include "../minishell.h"
#include "test.h"
#include <unistd.h>
#include <fcntl.h>

char *get_token_alias(t_token *token) {
	if (token == NULL)
		return "NULL";
	if (token->type == UNQUOTED_WORD)
		return "UW";
	if (token->type == DOUBLE_QUOTED_WORD)
		return "DW";
	if (token->type == SINGLE_QUOTED_WORD)
		return "SW";
	if (token->type == PIPE)
		return "P";
	if (token->type == INPUT_REDIRECTION)
		return "IR";
	if (token->type == HEREDOC_REDIRECTION)
		return "HR";
	if (token->type == OUTPUT_REDIRECTION)
		return "OR";
	if (token->type == APPEND_REDIRECTION)
		return "AR";
	if (token->type == DELIMITER)
		return "D";
	return "U";
}

t_token *quite_lexer(char *input)
{
	/* ignore error outputs */
	freopen("/dev/null", "w", stderr);
	t_token *head = lex(input);
	fclose(stderr);
	return head;
}

/**
 * @brief checks if the token matches the type and value.
 * 
 * Use this variables:
 * UW -> UNQUOTED_WORD
 * DW -> DOUBLE_QUOTED_WORD
 * SW -> SINGLE_QUOTED_WORD
 * IR -> INPUT_REDIRECTION
 * HR -> HEREDOC_REDIRECTION
 * OR -> OUTPUT_REDIRECTION
 * AR -> APPEND_REDIRECTION
 * D -> DELIMITER
 * P -> PIPE
 * U -> UNKNOWN
 *
 * put spaces between tokens. 
 * 
 * Example:
 * check_tokens(lex("a|b"), "UW P UW") -> 1
 * check_tokens(lex("a|b"), "UW UW") -> 0
 * check_tokens(lex("a | b"), "UW D P D UW") -> 1
 * 
 * @param lexer_input input string
 * @param expected_pseudo_input expected tokens
 * @return the lexer tokens
*/
t_token *check_lexer_output(char *lexer_input, char *expected_pseudo_input)
{
	t_token *head = quite_lexer(lexer_input);
	if (expected_pseudo_input == NULL)
	{
		cr_assert_null(head, "tokens was not null.\n\noutput   : %s\nexpected : %s", get_token_alias(head), expected_pseudo_input);
		return NULL;
	}

	return check_tokens(head, lexer_input, expected_pseudo_input);
}

t_token *check_tokens(t_token *head, char *lexer_input, char *expected_pseudo_input)
{
	int i = 0;
	int token_index = 0;
	t_token *token = head;
	int len = strlen(expected_pseudo_input);

	while (token && i < len) {
		char *alias = get_token_alias(token);
		int cmp_result = strncmp(alias, expected_pseudo_input + i, strlen(alias));	
		cr_assert_eq(cmp_result, 0, "unexpected tokens found.\n\ninput: %s\noutput[%d]: %s\nexpected : %s", lexer_input, token_index, alias, expected_pseudo_input);		
		token = token->next;
		i += strlen(alias) + 1;
		token_index++;
	}

	if (token) {
		t_token *cur = token;
		while (cur)
			cur = cur->next;
		cr_assert_null(token, "tokens was correct but there is over token.\n\ninput: %s\noutput[%d]: %s\nexpected : %s", lexer_input, token_index, get_token_alias(token), expected_pseudo_input);
	}
	cr_assert_eq(i >= len, 1, "tokens was correct but there is missing tokens.\n\ninput: %s\noutput[%d]: %s\nexpected : %s", lexer_input, token_index, "NULL", expected_pseudo_input);
	return head;
}