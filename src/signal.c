#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include "../includes/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include "../libft/libft.h"

t_signal_type signal_type;

void	handle_signal(int signum)
{
	(void) signum;
    rl_replace_line("", 0);
    printf("%s  \n", get_prompt());
    rl_on_new_line();
    rl_redisplay();
}

void register_signal_handler()
{
	signal(SIGINT,  handle_signal);
}
