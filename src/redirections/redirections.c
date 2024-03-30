#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int	redirect(t_redirection *redir, int *addr, int fd)
{
	redir->redir_fd = fd;
	*addr = fd;
	if (redir->redir_fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(redir->redirected);
		*get_exit_status() = 1;
		return 1;
	}
	return 0;
}

void close_old_fd(t_command *cur, t_redirection redir)
{
	if (redir.flags & INPUT && cur->input != STDIN_FILENO)
		close(cur->input);
	else if (!(redir.flags & INPUT) && cur->output != STDOUT_FILENO)
		close(cur->output);
}

int get_flags(t_redirection *redir)
{
	int flags;

	flags = 0;
	if (redir->flags & INPUT)
		flags |= O_RDONLY;
	else 
		flags |= O_WRONLY | O_CREAT | O_TRUNC;
	
	if (redir->flags & APPEND)
		flags |= O_APPEND;
	return flags;
}

void	handle_redirections(t_command *cur)
{
	int				i;
	t_redirection	redir;
	int				fd;
	int				*fd_addr;

	i = 0;
	while (cur->redirections[i].redirected)
	{
		redir = cur->redirections[i];
		close_old_fd(cur, redir);
		
		if (redir.flags & HEREDOC)
			fd = read_heredoc_input(redir.redirected);
		else
			fd = open(redir.redirected, get_flags(&redir), 0644);
		
		if (redir.flags & INPUT)
			fd_addr = &cur->input;
		else
			fd_addr = &cur->output;

		if (redirect(&redir, fd_addr, fd))
			return;
		i++;
	}
}

void	handle_file_redirections(t_command *cur)
{
	while(cur)
	{
		cur->output = STDOUT_FILENO;
		cur->input = STDIN_FILENO;
		handle_redirections(cur);
		cur = cur->next;
	}
}
