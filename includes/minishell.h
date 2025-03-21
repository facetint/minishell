/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 09:14:38 by hamza             #+#    #+#             */
/*   Updated: 2024/04/02 17:36:00 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "state_typedef.h"

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
}	t_token_type;

typedef enum e_signal_type
{
	IN_HEREDOC,
	WAITING_HEREDOC,
	RUNNING_COMMANDS,
	EXECUTING_CMD_IN_CHILD,
	PROMPT,
}	t_signal_type;

extern t_signal_type	g_signal_type;

/* if 1 input, otherwise, output */
/* 1 << 0 */
# define INPUT 1
/* only valid if IS_INPUT is 1*/
/* 1 << 1 */
# define APPEND 2
/* if 1 heredoc text, otherwise, string is a file name */
/* 1 << 2 */
# define HEREDOC 4

typedef struct s_redirection
{
	char	*redirected;
	int		redir_fd;
	int		flags;
}	t_redirection;

typedef struct s_command
{
	char				**args;
	int					output;
	int					input;
	int					pid;
	t_redirection		*redirections;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_file_descriptors
{
	int	inp_fd;
	int	out_fd;
	int	*prev_p;
	int	*next_p;
}	t_file_descriptors;

t_lexer_state	word_state(t_token **lexer_data,
					char *input, int *const i);
t_lexer_state	operator_state_l(t_token **lexer_data,
					char *input, int *const i);
t_lexer_state	delimiter_state(t_token **lexer_data,
					char *input, int *const i);

void			argument_state(t_token **lexer_data, t_command *command);
void			operator_state_p(t_token **lexer_data, t_command *command);

// lexer
t_token_type	get_meta_token_type(const char *input);
t_token			*get_last_lexer_data(t_token *token);
t_token			*lexer_data_new(t_token token);
t_token			*lex(char *input);
void			lexer_data_append(t_token **data, t_token *new_data);
void			lexer_data_insert(t_token *data, t_token *new_list);
void			unquote(t_token *lexer_data);
void			uninit_tokens(t_token *lexical_data);
int				is_in_single_quote(char *input, int index);
int				is_word(t_token_type type);
int				is_operator(t_token_type type);
void			unexpected_token_error(t_token *token);
int				is_there_lack_of_word(t_token *token);
int				validate_pipes(t_token *token);
void			handle_invalid_input(t_token *lexer_data);

// expander
void			expand(t_token **head);
void			internal_field_split(t_token **token, t_token**next_token_ptr);
void			expand_string(char **string);
char			*replace_string(char *input, int p_start,
					int p_len, char *replacement);
int				is_nameless_variable(t_token *token);
void			expand_token(t_token *token, t_token **head,
					t_token **token_ptr, t_token **prev_ptr, t_token**next_token);

// parser
t_command		*parse(t_token *lexer_data);
int				count_cmd_args(t_token *lexer_data);
int				count_cmd_redirections(t_token *lexer_data);
t_parser_state	decide_next_state(t_token **cur_token);
t_redirection	create_redirection_data(t_token **lexer_data);
void			join_all_composed_words(t_token **cur_token, char **string_ptr);

// main
char			*get_prompt(void);
void			unexpected_token_error(t_token *token);
void			handle_input(char *input);
void			handle_memory_error(void);
int				is_valid(t_token *lexer_data);

// utils
char			*ft_str_arr_join(char **str_list, unsigned int str_count);
char			*ft_unsafe_strdup(const char *str);

// executer
void			execute(t_command *cmds);
void			handle_command(t_command *cmd, int *prev_p, int *next_p);
char			*find_path(char *cmd);
void			close_fds(t_file_descriptors fds);
void			close_redirections(t_file_descriptors fds);
int				get_input_fd(int *pipe, t_command *cmd);
int				get_output_fd(int *pipe, t_command *cmd);
void			close_pipe(int *pipe);

// builtin
void			execute_builtin(t_command *cmd, int fd[2]);
int				isbuiltin(char *cmd);
void			builtin_exit(t_command *cmd);
void			builtin_echo(t_command *cmd, int fd[2]);
void			builtin_pwd(t_command *cmd);
void			builtin_export(t_command *cmd, int fd[2]);
void			export_env(char *format);
void			builtin_unset(t_command *cmd, int fd[2]);
int				should_run_in_child(t_command *cmd);
int				ft_strcmp(char *s1, char *s2);
void			builtin_cd(t_command *cmd);
void			execute_cd(char *str, t_command *cmd);
void			change_pwd(t_command *cmd);
void			change_old(char *str);

// heredocs and redirections
int				read_heredoc_input(char *delimiter);
void			handle_file_redirections(t_command *cur);

//signal
void			register_signal_handler(void);
void			handle_signal(int signum);

//exit status
int				*get_exit_status(void);

// abort
void			abort_function(void);

// error
void			path_error(char	*cmd);
void			pid_error(int *prev_pipe, int *next_pipe);

int				are_quotes_valid(t_token *token);
t_token			*do_ifs(char *str);
t_token			**find_token_ptr_before(t_token **head, t_token *tofind);

#endif
