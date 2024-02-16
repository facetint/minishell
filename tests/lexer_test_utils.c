#include <criterion/criterion.h>
#include "../minishell.h"
#include "test.h"
#include <unistd.h>
#include <fcntl.h>

char *get_token_alias(t_token *token)
{
	if (token == NULL)
		return "NULL";
	
	switch (token->type)
	{
		case UNQUOTED_WORD:
			return "UW";
		case DOUBLE_QUOTED_WORD:
			return "DW";
		case SINGLE_QUOTED_WORD:
			return "SW";
		case PIPE:
			return "P";
		case INPUT_REDIRECTION:
			return "IR";
		case HEREDOC_REDIRECTION:
			return "HR";
		case OUTPUT_REDIRECTION:
			return "OR";
		case APPEND_REDIRECTION:
			return "AR";
		case DELIMITER:
			return "D";
		default:
			return "U";
	}
}

/**
 * @brief returns the lexer's output. however all error outputs are ignored.
 * 
 * @param input input string
 * 
*/
t_token *quite_lexer(char *input)
{
	/* ignore error outputs */
	freopen("/dev/null", "w", stderr);
	t_token *head = lex(input);
	fclose(stderr);
	return head;
}

/**
 * @brief returns NULL if the lexer output is not equal to the expected pseudo input.
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
 * Put spaces between pseudo tokens. 
 * 
 * Example:
 * check_lexer_output(lex("a|b"), "UW P UW") -> VALID
 * check_lexer_output(lex("a|b"), "UW UW") -> INVALID (returns NULL)
 * check_lexer_output(lex("a | b"), "UW D P D UW") -> VALID
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

	if (token)
	{
		t_token *cur = token;
		while (cur)
			cur = cur->next;
		cr_assert_null(token, "tokens was correct but there is over token.\n\ninput: %s\noutput[%d]: %s\nexpected : %s", lexer_input, token_index, get_token_alias(token), expected_pseudo_input);
	}
	cr_assert_eq(i >= len, 1, "tokens was correct but there is missing tokens.\n\ninput: %s\noutput[%d]: %s\nexpected : %s", lexer_input, token_index, "NULL", expected_pseudo_input);
	return head;
}