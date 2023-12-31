#ifndef PARSER_H
# define PARSER_H

typedef enum s_token_type
{
	DOUBLE_QUOTED_WORD,
	SINGLE_QUOTED_WORD,
	UNQUOTED_WORD,
	PIPE,
	OUTPUT_REDIRECTION,
	INPUT_REDIRECTION,
	HEREDOC_REDIRECTION,
	APPEND_REDIRECTION,
	DELIMITER,
	UNKNOWN,
} t_token_type;


/* if 1 input, otherwise, output */
# define INPUT (1 << 0)
/* only valid if IS_INPUT is 1*/
# define APPEND (1 << 1)
/* if 1 heredoc text, otherwise, string is a file name */
# define HEREDOC (1 << 2)
typedef struct s_redirection
{
	char *redirected; /* non-null */
	int flags;
} t_redirection;

typedef struct s_command
{
	char *name;
	char **args;
	t_redirection *redirections;
	struct s_command *next; /* output->input redirected command */
} t_command;

typedef struct s_token
{
	char *value;
	t_token_type type;
	struct s_token *next;
} t_token;

void unexpected_token_error(t_token *token);

#define LEXER_STATE_FUNCTION_PARAMETERS t_token **lexer_data, char *input, int *const index

typedef void *(*lexer_func)(LEXER_STATE_FUNCTION_PARAMETERS);
typedef lexer_func *(*lexer_state)(LEXER_STATE_FUNCTION_PARAMETERS);

lexer_state word_state(LEXER_STATE_FUNCTION_PARAMETERS);
lexer_state operator_state_l(LEXER_STATE_FUNCTION_PARAMETERS);
lexer_state delimiter_state(LEXER_STATE_FUNCTION_PARAMETERS);

#define PARSER_STATE_FUNCTION_PARAMETERS t_token **lexer_data, t_command *command

typedef void *(*parser_func)(PARSER_STATE_FUNCTION_PARAMETERS);
typedef parser_func *(*parser_state)(PARSER_STATE_FUNCTION_PARAMETERS);

parser_state command_state(PARSER_STATE_FUNCTION_PARAMETERS);
parser_state argument_state(PARSER_STATE_FUNCTION_PARAMETERS);
parser_state operator_state_p(PARSER_STATE_FUNCTION_PARAMETERS);

t_token_type get_meta_token_type(const char *input);

t_token *get_last_lexer_data(t_token *token);
t_token *lexer_data_new(t_token token);
void lexer_data_append(t_token **data, t_token *new_data);
void lexer_data_insert(t_token **data, t_token *new_list);
t_token **find_pointer_to_next(t_token **data, t_token *target);

int is_valid(t_token *lexer_data);

t_token *lex(char *input);
void expand(t_token **head);
void internal_field_split(t_token **head, t_token *token);
void unquote(t_token *lexer_data);
t_command *parse(t_token *lexer_data);
void uninit_tokens(t_token *lexical_data);

int is_in_single_quote(char *input, int index);

int is_word(t_token_type type);
int is_operator(t_token_type type);

#endif
