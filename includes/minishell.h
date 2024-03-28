#ifndef MINISHELL_H
# define MINISHELL_H

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
    WAITING_HEREDOC,
	RUNNING_COMMANDS,
	EXECUTING_CMD_IN_CHILD,
    PROMPT,
} t_signal_type;

extern t_signal_type signal_type;

/* if 1 input, otherwise, output */
# define INPUT (1 << 0)
/* only valid if IS_INPUT is 1*/
# define APPEND (1 << 1)
/* if 1 heredoc text, otherwise, string is a file name */
# define HEREDOC (1 << 2)

typedef struct s_redirection
{
	char *redirected; /* non-null */
	int redir_fd;
	int flags;
} t_redirection;

typedef struct s_command
{
	char			**args;
	int				output;
	int				input;
	int				pid;
	t_redirection	*redirections;
	struct s_command *next;
	struct s_command *prev;
} t_command;

typedef struct s_token
{
	char *value;
	t_token_type type;
	struct s_token *next;
} t_token;


#define LEXER_STATE_FUNCTION_PARAMETERS t_token **lexer_data, char *input, int *const index

typedef void *(*lexer_state)(LEXER_STATE_FUNCTION_PARAMETERS); //todo rename as t_lexer...

lexer_state word_state(LEXER_STATE_FUNCTION_PARAMETERS);
lexer_state operator_state_l(LEXER_STATE_FUNCTION_PARAMETERS);
lexer_state delimiter_state(LEXER_STATE_FUNCTION_PARAMETERS);

#define PARSER_STATE_FUNCTION_PARAMETERS t_token **lexer_data, t_command *command

typedef void *(*parser_state)(PARSER_STATE_FUNCTION_PARAMETERS);//todo rename as t_parser...

void argument_state(PARSER_STATE_FUNCTION_PARAMETERS);
void operator_state_p(PARSER_STATE_FUNCTION_PARAMETERS);

// lexer
t_token_type get_meta_token_type(const char *input);
t_token *get_last_lexer_data(t_token *token);
t_token *lexer_data_new(t_token token);
t_token *lex(char *input);
void lexer_data_append(t_token **data, t_token *new_data);
void lexer_data_insert(t_token *data, t_token *new_list);
void unquote(t_token *lexer_data);
void uninit_tokens(t_token *lexical_data);
int is_in_single_quote(char *input, int index);
int is_word(t_token_type type);
int is_operator(t_token_type type);
void unexpected_token_error(t_token *token);

// expander
void expand(t_token **head);
void internal_field_split(t_token **token);
void insert_uword_tokens(t_token **token_ptr, char **strings);
void	expand_string(char **string);

// parser
t_command *parse(t_token *lexer_data);

// main
char *get_prompt();
void unexpected_token_error(t_token *token);
void handle_input(char *input);
void handle_memory_error(void);
int is_valid(t_token *lexer_data);

// debug
void debug(t_token *token, t_command *cmd);
char *ft_str_arr_join(char **str_list, unsigned int str_count);

// executer
void	execute(t_command *cmds);
void    handle_command(int input_fd, int output_fd, t_command *cmd, int *prev_pipe, int *next_pipe);
char	*find_path(char *cmd);
void	print_and_close(int fd);
void    run_by_type(t_command *cmd, char *path_cmd);
void	pid_error(int pid, int *prev_pipe, int *next_pipe);
void	dup2_and_close(int inp_fd, int out_fd, int *prev_p, int *next_p);
void	path_error(t_command *cmd);

// builtin

void    handle_builtin(t_command *cmd, int fd[2]);
int		isbuiltin(char *cmd);
void	builtin_exit(t_command *cmd);
void	builtin_echo(t_command *cmd, int fd[2]);
void    builtin_pwd(t_command *cmd);
void    builtin_export(t_command *cmd, int fd[2]);
void    builtin_unset(t_command *cmd, int fd[2]);
int 	ft_strcmp(char *s1, char *s2);

// cd
void    builtin_cd(t_command *cmd);
void    execute_cd(char *str, t_command *cmd);
void    change_pwd(t_command *cmd);
void    change_old(char *str);


// heredocs
int		read_heredoc_input(char *delimiter);
int		handle_heredocs(t_command *cur);
void	link_heredoc_input(t_command *cmd);

//file redirections
void create_file(char *file);
int open_file(char *file, int append);
t_redirection *get_input_redir(t_command *cmd);
t_redirection *get_output_redir(t_command *cmd);

//signal
void register_signal_handler();
void handle_signal(int signum);

// global
int *get_exit_status();

// abort
void	abort_function();
#endif
