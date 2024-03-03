#ifndef PARSER_H
# define PARSER_H

typedef enum e_token_type
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

typedef enum e_signal_type
{
    IN_HEREDOC,
    DEFAULT,
} t_signal_type;

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
	int fd;
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

typedef void *(*lexer_state)(LEXER_STATE_FUNCTION_PARAMETERS); //todo rename as t_lexer...

lexer_state word_state(LEXER_STATE_FUNCTION_PARAMETERS);
lexer_state operator_state_l(LEXER_STATE_FUNCTION_PARAMETERS);
lexer_state delimiter_state(LEXER_STATE_FUNCTION_PARAMETERS);

#define PARSER_STATE_FUNCTION_PARAMETERS t_token **lexer_data, t_command *command

typedef void *(*parser_state)(PARSER_STATE_FUNCTION_PARAMETERS);//todo rename as t_parser...

parser_state command_state(PARSER_STATE_FUNCTION_PARAMETERS);
parser_state argument_state(PARSER_STATE_FUNCTION_PARAMETERS);
parser_state operator_state_p(PARSER_STATE_FUNCTION_PARAMETERS);

t_token_type get_meta_token_type(const char *input);

t_token *get_last_lexer_data(t_token *token);
t_token *lexer_data_new(t_token token);
void lexer_data_append(t_token **data, t_token *new_data);
void lexer_data_insert(t_token *data, t_token *new_list);

int is_valid(t_token *lexer_data);

t_token *lex(char *input);
void expand(t_token **head);
void internal_field_split(t_token **token);
void insert_uword_tokens(t_token **token_ptr, char **strings);
void unquote(t_token *lexer_data);
t_command *parse(t_token *lexer_data);
void uninit_tokens(t_token *lexical_data);

int is_in_single_quote(char *input, int index);

int is_word(t_token_type type);
int is_operator(t_token_type type);

char *get_prompt();
void unexpected_token_error(t_token *token);
void handle_input(char *input);
void handle_memory_error(void);

void debug(t_token *token, t_command *cmd);
char *ft_str_arr_join(char **str_list, unsigned int str_count);

// executer
void	execute(t_command *cmds, t_command *beginCmds);
char	*find_path(char *cmd);

// builtin
int		isbuiltin(char *cmd);
void	builtin_exit(t_command *cmd);
void	builtin_echo(t_command *cmd, int fd[2]);
void    builtin_pwd(t_command *cmd);
void    builtin_export(t_command *cmd, int fd[2]);
void    builtin_unset(t_command *cmd);
void    builtin_cd(t_command *cmd);
void    handle_builtin(t_command *cmd, int fd[2]);


#endif
