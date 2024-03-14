/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:46:34 by facetint          #+#    #+#             */
/*   Updated: 2024/03/14 16:51:51 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "../../libft/libft.h"
#include "../../memory-allocator/allocator.h"
#include "../../includes/env.h"
#include "../../get_next_line/get_next_line.h"

t_envList	*get_global_env()
{
	static	t_envList env = (t_envList){0};
	return (&env);
}

void	print_and_close(int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		ft_putstr_fd(line, 1);
		safe_free(line);
	}
	close(fd);
}

char    *find_path(char *cmd)
{
    char    *path;
    char    **path_arr;
    char    *joined_path;
    char    *new_joined_path;
    int     counter;

    path = getenv("PATH");
    path_arr = ft_split(path, ':');

    counter = 0;
    while (path_arr[counter])
    {
        joined_path = ft_strjoin(path_arr[counter], "/");
        new_joined_path = ft_strjoin(joined_path, cmd);
        safe_free(joined_path);
        if (access(new_joined_path, F_OK) == 0)
        {
            safe_free(path_arr);
            return (new_joined_path);
        }
        counter++;
    }
    return (NULL);
}