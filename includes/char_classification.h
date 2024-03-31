/**
 * @file char_classification.h
 * @file char_classification.c
 * 
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


int is_field_terminator(char c);
int	is_meta_char(char c);
int is_whitespace(char c);
int is_quote(char c);
int is_unquoted_word_char(char c);
int	is_name_char(char c);