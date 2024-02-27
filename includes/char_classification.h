/**
 * @file char_classification.h
 * @brief This file contains macros and enums for character classification.
 *
 * @description This file completely defines what our shell should understand when it
 * comes to characters.
 *
 * @note This file completely defines what our shell should understand regarding
 * characters. If this file makes you feel like we just told you that cars
 * have 4 wheels, then you are right. But we need to be explicit about it.
 *
 * @note You can find tons of code that does not care about these details. and
 * probably you'll see that they going to be a soup instead of being a code.
 * This file is very critical. So we carefully read the manual before and
 * during writing this file.
 **/

typedef enum s_quote
{
	DOUBLE_QUOTE = '\"',
	SINGLE_QUOTE = '\''
} t_quote;

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
# define is_field_terminator(c) (c == ' ' || c == '\t' || c == '\n')

/**
 * @brief The manual defines meta characters as: "A character that, when unquoted,
 * separates words.". They tell us a word is over and, we should start a new token.
 *
 * And it continues: "A metacharacter is a >space, tab, newline, or one of the following characters:
 * ‘|’, ‘&’, ‘;’, ‘(’, ‘)’, ‘<’, or ‘>’."
 */
# define is_meta_char(c) (c == ' ' || c == '\t' || c == '\n' || c == '|' || c == '<' || c == '>')

/**
 * @brief The manual does not define whitespaces explicitly. But I think we don't need a definition.
 */
# define is_whitespace(c) (c == ' ' || c == '\t')

/**
 * @brief The manual defines quotes as " and '. (We don't care about backticks(`))
 */
# define is_quote(c) (c == DOUBLE_QUOTE || c == SINGLE_QUOTE)

/**
 * @brief The manual explicitly says that a word cannot contain a meta character without
 * being quoted. And we know an 'unquoted word' is a word that is not quoted.
 */
# define is_unquoted_word_char(c) (!is_meta_char(c) && !is_quote(c))

/**
 * @brief The manual defines a 'name' as "A word consisting solely of letters, numbers, and underscores,
 * and beginning with a letter or underscore. Names are used as shell variable and function names.
 * Also referred to as an identifier."
 *
 * But we don't care about the first letter rule. Probably we should not. Here is why: todo
 *
 * In bash, variable names with digits($0,$1...) are reserved for the positional parameters.
 * (See manual: 3.4.1 Positional Parameters) but our implementation does not have positional parameters.
 * In a nutshell we allow variable names with digits. Because of we can. lol.
 *
 */
# define is_name_char(c) (ft_isalnum(c) || c == '_')
