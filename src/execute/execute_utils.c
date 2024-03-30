/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:46:34 by facetint          #+#    #+#             */
/*   Updated: 2024/03/30 17:09:22 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>
#include <sys/wait.h>
#include "../../libft/libft.h"
#include "../../memory-allocator/allocator.h"
#include "../../includes/env.h"
#include <stdio.h>
#include <sys/stat.h>

int	is_path(char *str)
{
	return ((str[0] == '.' && str[1] == '/') || str[0] == '/');
}

char	*find_path(char *cmd)
{
	char	*path;
	char	**path_arr;
	char	*search_path;
	int		counter;
	struct stat buf;

	stat(cmd, &buf);
	if (S_ISDIR(buf.st_mode))
		exit(126);
	if (is_path(cmd) && access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path = find_env("PATH");
	if (!path)
		return (path_error(cmd), NULL);
	path_arr = ft_split(path, ':');
	counter = 0;
	while (path_arr[counter])
	{
		search_path = ft_str_arr_join((char *[])
			{path_arr[counter], "/", cmd}, 3);
		if (access(search_path, F_OK) == 0)
		{
			safe_free(path_arr);
			return (search_path);
		}
		counter++;
	}
	return (path_error(cmd), NULL);
}

int	should_run_in_child(t_command *cmd)
{
	return (cmd->prev || cmd->next || !isbuiltin(cmd->args[0]));
}
