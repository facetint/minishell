#ifndef PARSER_H
# define PARSER_H

typedef enum s_token_type {
	COMMAND,
	DOUBLE_QUOTED_ARGUMENT,
	SINGLE_QUOTED_ARGUMENT,
	ARGUMENT,
	PIPE,
	OUTPUT_REDIRECTION,
	INPUT_REDIRECTION,
	HEREDOC_REDIRECTION,
	APPEND_REDIRECTION,
	UNKNOWN,
} t_token_type;

typedef enum s_quote {
	DOUBLE_QUOTE = '\"',
	SINGLE_QUOTE = '\''
} t_quote;

typedef struct s_token {
	int start;
	int end;
	t_token_type type;
	struct s_token *next;
} t_token;

#endif
