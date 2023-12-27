#ifndef PARSER_H
# define PARSER_H

typedef enum s_token_type {
	COMMAND,
	DOUBLE_QUOTED_ARGUMENT,
	SINGLE_QUOTED_ARGUMENT,
	UNQUOTED_ARGUMENT,
	PIPE,
	OUTPUT_REDIRECTION,
	INPUT_REDIRECTION,
	HEREDOC_REDIRECTION,
	APPEND_REDIRECTION,
	WORD,
	IFS, // Internal Field Separator. See 3.5.7 Word Splitting
	UNKNOWN,
} t_token_type;

typedef enum s_quote {
	DOUBLE_QUOTE = '\"',
	SINGLE_QUOTE = '\''
} t_quote;

typedef struct s_command {
	char *name;
	char **args;
	char *input_file;
	char *output_file;
	char *heredoc;
	int append;
	struct s_command *next;
} t_command;

typedef struct s_token {
	int start;
	int end;
	t_token_type type;
	struct s_token *next;
} t_token;

void unexpected_token_error(char token);

#define STATE_FUNCTION_PARAMETERS t_token **lexer_data, char *input, int index

typedef void *(*func_to_func_ptr)(STATE_FUNCTION_PARAMETERS);
typedef func_to_func_ptr *(*state)(STATE_FUNCTION_PARAMETERS);

state command_state(STATE_FUNCTION_PARAMETERS);
state argument_state(STATE_FUNCTION_PARAMETERS);
state command_after_state(STATE_FUNCTION_PARAMETERS);
state delimiter_state(STATE_FUNCTION_PARAMETERS);
state redirection_word_state(STATE_FUNCTION_PARAMETERS);

t_token_type get_meta_token_type(const char *input);
int get_index(t_token *token);

t_token *get_last_lexer_data(t_token *token);
t_token *lexer_data_new(t_token token);
void lexer_data_append(t_token **data, t_token *new_data);

int are_redirections_valid(t_token *lexer_data);
int are_quotes_valid(const char *input, t_token *lexer_data);
int are_pipes_valid(t_token *lexer_data);

t_token *lexer(char *input);
t_token *expand_lexer_data(char *input, t_token *lexer_data);
int is_in_single_quote(char *input, int index);

t_token *lex(char *input);
state word_state(t_token **lexer_data, char *input, int index);
state meta_state(t_token **lexer_data, char *input, int index);

#endif
