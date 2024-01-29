#include <criterion/criterion.h>
#include "../minishell.h"
#include "test.h"

Test(lexer, pipe_test)
{
	check_tokens("echo a | cat", "UW D UW D P D UW");
	t_token *token = check_tokens("a\\ | b", "UW P D UW");
	cr_assert_str_eq(token->value, "a\\ ");
}

Test(lexer, simple_double_quoted_pipe_test)
{
	t_token *token = check_tokens("echo \"a\" | cat", "UW D DW D P D UW");
	cr_assert_str_eq(token->next->next->value, "\"a\"");
}

Test(lexer, mixed_word_types_test)
{
	t_token *token = check_tokens("ec'h'\"o\" b|cat", "UW SW DW D UW P UW");
	cr_assert_str_eq(token->value, "ec");
	cr_assert_str_eq(token->next->value, "'h'");
	cr_assert_str_eq(token->next->next->value, "\"o\"");
	cr_assert_str_eq(token->next->next->next->next->value, "b");

	check_tokens("'\\'A", "SW UW");
}

Test(lexer, simple_redirection_test)
{
	check_tokens("echo a > b", "UW D UW D OR D UW");
}

Test(lexer, simple_double_redirection_test)
{
	check_tokens("echo a >> b", "UW D UW D AR D UW");
}

Test(lexer, simple_input_redirection_test)
{
	check_tokens("echo a < b", "UW D UW D IR D UW");
}

Test(lexer, simple_heredoc_redirection_test)
{
	check_tokens("echo a << b", "UW D UW D HR D UW");
}

Test(lexer, no_delimiter_test)
{
	check_tokens("a|b<c|d>e|f<<g>>h", "UW P UW IR UW P UW OR UW P UW HR UW AR UW");
}

Test(lexer, empty_input_test)
{
	check_tokens("", NULL);
	check_tokens("''", "SW");
	check_tokens("\"\"", "DW");
	check_tokens("\"\"''", "DW SW");
	check_tokens("''\"\"", "SW DW");
}

Test(lexer, delimiter_only_test)
{
	check_tokens("             \t\t", NULL);
}

Test(lexer, word_surrounded_by_delimiters_test)
{
	check_tokens("          \t\t     a\t          \t    ", "UW");
}

Test(lexer, quoted_pipe_test)
{
	check_tokens("a '|' b", "UW D SW D UW");
	check_tokens("a \"|\" b", "UW D DW D UW");
	check_tokens("a \\| b", "UW D UW D UW");
}

Test(lexer, quoted_redirection_test)
{
	check_tokens("a '>' b", "UW D SW D UW");
	check_tokens("a \">\" b", "UW D DW D UW");
	check_tokens("a \\> b", "UW D UW D UW");
}

Test(lexer, invalid_pipe_test)
{
	check_tokens("a|", "UW P");
	check_tokens("|a", "P UW");
	check_tokens("|", "P");
	check_tokens("a||b", "UW P P UW");
}

Test(lexer, invalid_redirection_test)
{
	check_tokens("a>", "UW OR");
	check_tokens(">", "OR");
	check_tokens("a>>", "UW AR");
	check_tokens(">>", "AR");
	check_tokens("a<", "UW IR");
	check_tokens("<", "IR");
	check_tokens("a<<", "UW HR");
	check_tokens("<<", "HR");
}

Test(lexer, invalid_word_test)
{
	check_tokens("<<<<<", "HR HR IR");
	check_tokens("|||||", "P P P P P");
	check_tokens(">>>>>>>>", "AR AR AR AR");
	check_tokens("|<|<<|>>|<<", "P IR P HR P AR P HR");
}

Test(lexer, invalid_quote_test) 
{
	check_tokens("\"", "DW");
	check_tokens("'", "SW");
	check_tokens("\"\\\"A", "DW");
}
