#include <stdio.h>
#include "../includes/minishell.h"
#include "../libft/libft.h"
#include "../memory-allocator/allocator.h"


int isbuiltin(char *cmd)
{
    if (ft_strncmp(cmd, "echo", ft_strlen("echo")) == 0)
        return (1);
    if (ft_strncmp(cmd, "export", ft_strlen("export")) == 0)
        return (1);
    if (ft_strncmp(cmd, "env", ft_strlen("env")) == 0)
        return(1);
    if (ft_strncmp(cmd, "exit", ft_strlen("exit")) == 0)
        return (1);
    if (ft_strncmp(cmd, "pwd", ft_strlen("pwd")) == 0)
        return (1);
    if (ft_strncmp(cmd, "cd", ft_strlen("cd")) == 0)
        return(1);
    if (ft_strncmp(cmd, "unset", ft_strlen("unset")) == 0)
        return(1);
    return (0);
}

void    handle_builtin(t_command *cmd)
{
    if (ft_strncmp(cmd->name, "echo", ft_strlen("echo")) == 0)
        return;
    if (ft_strncmp(cmd->name, "export", ft_strlen("export")) == 0)
        return;
    if (ft_strncmp(cmd->name, "env", ft_strlen("env")) == 0)
        return;
    if (ft_strncmp(cmd->name, "exit", ft_strlen("exit")) == 0)
        return;
    if (ft_strncmp(cmd->name, "pwd", ft_strlen("pwd")) == 0)
        return;
    if (ft_strncmp(cmd->name, "cd", ft_strlen("cd")) == 0)
        return;
    if (ft_strncmp(cmd->name, "unset", ft_strlen("unset")) == 0)
        return;
}