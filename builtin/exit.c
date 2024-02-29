#include "../libft/libft.h"
#include "../includes/minishell.h"
#include <unistd.h>
#include <stdio.h>
#include "../includes/env.h"

int count_args(char **args)
{
    int i;

    i = 0;
    while (args[i])
        i++;
    return (i);
}

void    builtin_exit(t_command *cmd)
{
    char    **arr;
    int     i;
    int     size;

    arr = cmd->args;
    i = 0;
    
}