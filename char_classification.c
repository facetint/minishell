#include "parser.h"
#include "libft/libft.h"

/**
 * @brief The manual defines meta characters as: "A character that, when unquoted,
 * separates words.". They tell us a word is over and we should start a new
 * token.
 * @param char variable to compare
 * @return 1 if meta character, 0 otherwise
 */
int is_meta_char(char c)
{
	return c == ' ' || c == '\t' || c == '\n' ||
	       c == '|' || c == '<' || c == '>';
	// c == '&' || c == ';' || c == '(' || c == ')'
}

/**
 * @brief In the manual (3.5.7 Word Splitting) it says:
 * "The shell treats each character of IFS(Internal Field Seperator) as a delimiter
 * and splits the results of the other expansions into words on these characters."
 * <br/><br/>
 * "If IFS is unset, or its value is exactly <strong>\<space\>\<tab\>\<newline\></strong>"
 *
 * @param char variable to compare
 * @return 1 if field terminator, 0 otherwise
 */
int is_field_terminator(char c)
{
	return c == ' ' || c == '\t' || c == '\n';
}

int is_whitespace(char c)
{
	return c == ' ' || c == '\t';
}

int is_quote(char c)
{
	return c == DOUBLE_QUOTE || c == SINGLE_QUOTE;
}

/* deprecated */
int is_name_char(char c)
{
	return !is_meta_char(c) && !is_whitespace(c) && !is_quote(c);
}

int is_name_char2(char c)
{
	return ft_isalnum(c) || c == '_';
}
