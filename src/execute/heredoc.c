#include <stdio.h>
#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <readline/readline.h>

void heredoc_to_fd(char *delimiter, int output_fd)
{
	char *line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, delimiter, INT_MAX) == 0)
			break;
		if (!*line)
			line = ft_strdup("\n");
		else
			expand_string(&line);
		ft_putstr_fd(line, output_fd);
		ft_putstr_fd("\n", output_fd);
		free(line);
	}
}

int read_heredoc_input(char *delimiter)
{
	int exit_status;
	int pid;
	int pipe_fd[2];

	pipe(pipe_fd);
	signal_type = WAITING_HEREDOC;
	pid = fork();
	if (pid < 0)
		return -1;
	if (pid == 0)
	{
		close(pipe_fd[0]);
		signal_type = IN_HEREDOC;
		heredoc_to_fd(delimiter, pipe_fd[1]);
		exit(0);
	} else {
		close(pipe_fd[1]);
		waitpid(pid, &exit_status, 0);
		exit_status >>= 8;
		if (exit_status != 0)
			return -1;
		return pipe_fd[0];
	}
}

