#ifndef TEST_H
# define TEST_H

# include "../minishell.h"

t_token *check_lexer_output(char *input, char *expected_pseudo_input);
t_token *quite_lexer(char *input);
t_token *check_tokens(t_token *head, char *lexer_input, char *expected_pseudo_input);

#endif
