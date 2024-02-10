#include <criterion/criterion.h>
#include "../minishell.h"
#include "test.h"

Test(lexer, pipe_test)
{
	check_lexer_output("echo a | cat", "UW D UW D P D UW");
	t_token *token = check_lexer_output("a\\ | b", "UW P D UW");
	cr_assert_str_eq(token->value, "a\\ ");
}

Test(lexer, simple_double_quoted_pipe_test)
{
	t_token *token = check_lexer_output("echo \"a\" | cat", "UW D DW D P D UW");
	cr_assert_str_eq(token->next->next->value, "\"a\"");
}

Test(lexer, mixed_word_types_test)
{
	t_token *token = check_lexer_output("ec'h'\"o\" b|cat", "UW SW DW D UW P UW");
	cr_assert_str_eq(token->value, "ec");
	cr_assert_str_eq(token->next->value, "'h'");
	cr_assert_str_eq(token->next->next->value, "\"o\"");
	cr_assert_str_eq(token->next->next->next->next->value, "b");
}

Test(lexer, simple_redirection_test)
{
	check_lexer_output("echo a > b", "UW D UW D OR D UW");
}

Test(lexer, simple_double_redirection_test)
{
	check_lexer_output("echo a >> b", "UW D UW D AR D UW");
}

Test(lexer, simple_input_redirection_test)
{
	check_lexer_output("echo a < b", "UW D UW D IR D UW");
}

Test(lexer, simple_heredoc_redirection_test)
{
	check_lexer_output("echo a << b", "UW D UW D HR D UW");
}

Test(lexer, no_delimiter_test)
{
	check_lexer_output("a|b<c|d>e|f<<g>>h", "UW P UW IR UW P UW OR UW P UW HR UW AR UW");
}

Test(lexer, empty_input_test)
{
	check_lexer_output("", NULL);
	check_lexer_output("''", "SW");
	check_lexer_output("\"\"", "DW");
	check_lexer_output("\"\"''", "DW SW");
	check_lexer_output("''\"\"", "SW DW");
}

Test(lexer, delimiter_only_test)
{
	check_lexer_output("             \t\t", NULL);
}

Test(lexer, word_surrounded_by_delimiters_test)
{
	check_lexer_output("          \t\t     a\t          \t    ", "UW");
}

Test(lexer, quoted_pipe_test)
{
	check_lexer_output("a '|' b", "UW D SW D UW");
	check_lexer_output("a \"|\" b", "UW D DW D UW");
	check_lexer_output("a \\| b", "UW D UW D UW");
}

Test(lexer, quoted_redirection_test)
{
	check_lexer_output("a '>' b", "UW D SW D UW");
	check_lexer_output("a \">\" b", "UW D DW D UW");
	check_lexer_output("a \\> b", "UW D UW D UW");
}

Test(lexer, invalid_pipe_test)
{
	check_lexer_output("a|", "UW P");
	check_lexer_output("|a", "P UW");
	check_lexer_output("|", "P");
	check_lexer_output("a||b", "UW P P UW");
}

Test(lexer, invalid_redirection_test)
{
	check_lexer_output("a>", "UW OR");
	check_lexer_output(">", "OR");
	check_lexer_output("a>>", "UW AR");
	check_lexer_output(">>", "AR");
	check_lexer_output("a<", "UW IR");
	check_lexer_output("<", "IR");
	check_lexer_output("a<<", "UW HR");
	check_lexer_output("<<", "HR");
}

Test(lexer, invalid_word_test)
{
	check_lexer_output("<<<<<", "HR HR IR");
	check_lexer_output("|||||", "P P P P P");
	check_lexer_output(">>>>>>>>", "AR AR AR AR");
	check_lexer_output("|<|<<|>>|<<", "P IR P HR P AR P HR");
}

Test(lexer, invalid_quote_test) 
{
	check_lexer_output("\"", "DW");
	check_lexer_output("'", "SW");
	check_lexer_output("\"\\\"A", "DW");
	check_lexer_output("'\\'A", "SW");
}
