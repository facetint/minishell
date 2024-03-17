/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:34:07 by facetint          #+#    #+#             */
/*   Updated: 2024/03/17 07:57:36 by hcoskun42        ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "stdio.h"
#include <sys/wait.h>
#include <stdlib.h>
#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include "../../includes/env.h"

void	link_heredoc_input(t_command *cmd)
{
    int    i;

    i = 0;
    while (cmd->redirections[i].redirected)
    {
        if (cmd->redirections[i].flags & HEREDOC)
        {
			close(0);
            dup2(cmd->redirections[i].input_fd, STDIN_FILENO);
            close(cmd->redirections[i].input_fd);
        }
        i++;
	}
}

void    run_by_type(t_command *cmd, char *path_cmd)
{
	link_heredoc_input(cmd);
    if (isbuiltin(cmd->args[0]))
    {
        int new_fd[2];
        new_fd[1] = 1;
        handle_builtin(cmd, new_fd);
        exit(0);
    }
    else
    {
        execve(path_cmd, cmd->args, to_arr(get_global_env()));
        exit(127);
    }
}
void	execute_command(t_command *cmd, t_command *prev, int fd[2])
{
	char	*path_cmd;
    int		pid;

    pid = fork();
    if (pid == -1)
        return ft_putstr_fd("Fork error!", 2); //todo exit
    if (pid != 0) {
		cmd->pid = pid;
        return ;
	}
	path_cmd = find_path(cmd->args[0]);
	if (!path_cmd)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(cmd->args[0], 2);
        ft_putstr_fd(": command not found\n", 2);
        exit(127);
    }
    if (prev)
    {
        dup2(prev->output, STDIN_FILENO);
        close(prev->output);
    }
    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);
    run_by_type(cmd, path_cmd);
}

void	handle_command(t_command *prev, t_command *cmd)
{
	t_redirection *out_redir;
	
	int	fd[2];

    if (pipe(fd) == -1)
        return ft_putstr_fd("Pipe error!", 2); //todo exit
    execute_command(cmd, prev, fd);
    close(fd[1]);
    if (prev)
       close(prev->output);
    if (!cmd->next)
        return print_and_close(fd[0]);
    cmd->output = fd[0];
	out_redir = get_output_redir(cmd);
	if (out_redir)
		cmd->output = open_file(out_redir->redirected, cmd->redirections->flags & APPEND);    
}

void	execute(t_command *cmds)
{
	t_command	*cur;
	t_command	*prev;
	int			exit_status;

	if (!cmds->next && cmds->args[0] && isbuiltin(cmds->args[0]))
		return handle_builtin(cmds, (int[]){0, 1});

    cur = cmds;
    prev = NULL;
    while (cur)
    {
        handle_command(prev, cur);
        prev = cur;
        cur = cur->next;
    }

	waitpid(prev->pid, &exit_status, 0);
	*get_exit_status() = exit_status >> 8;
	while(wait(NULL) > 0);
}
