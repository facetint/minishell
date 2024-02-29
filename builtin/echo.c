#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>

int is_n_option(char *str)
{
    int i;
    int len;

    if (!str)
        return 0;
    len = ft_strlen(str);
    if (len < 2)
        return 0;
    if (str[0] != '-')
        return 0;
    i = 1;
    while (str[i] == 'n')
        i++;
    if (i == len)
        return 1;
    return 0;
}

void builtin_echo(t_command *cmd)
{
    char    **args;
    int     i;
    int     n_option;

    args = cmd->args;
    i = 0;
    n_option = 0;
    while (is_n_option(args[i]))
        i++;
    if (i > 0)
        n_option = 1;
    while (args[i])
    {
        ft_putstr_fd(args[i], 1);
        if (args[i + 1] != NULL)
            ft_putstr_fd(" ", 1);
        i++;
    }
    if (!n_option)
        ft_putstr_fd("\n", 1);
}