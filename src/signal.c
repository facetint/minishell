#include <signal.h>
#include <stdio.h>
#include "../includes/minishell.h"
#include <readline/readline.h>
#include <stdlib.h>

t_signal_type signal_type;

void	handle_signal(int signum)
{
	(void) signum;

	*get_exit_status() = 1;
	if (signal_type == PROMPT) {
		printf("%s%s  \n", get_prompt(), rl_line_buffer);
		//rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	} else if (signal_type == RUNNING_COMMANDS) {
		printf("\n");
		//rl_replace_line("", 0);
		rl_on_new_line();
		*get_exit_status() = 128 + signum;
	} else if (signal_type == IN_HEREDOC) {
		printf("> %s  \n", rl_line_buffer);
		//rl_replace_line("", 0);
		rl_on_new_line();
		exit(1);
	}
}


void register_signal_handler() 
{
	signal(SIGINT,  handle_signal);
}
