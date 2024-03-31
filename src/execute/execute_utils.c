/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:46:34 by facetint          #+#    #+#             */
/*   Updated: 2024/03/31 06:13:17 by hamza            ###   ########.fr       */
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

int	should_run_in_child(t_command *cmd)
{
	return (cmd->prev || cmd->next || !isbuiltin(cmd->args[0]));
}

int	is_directory(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == -1)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

char	*find_path(char *cmd)
{
	char		*path;
	char		**path_arr;
	char		*search_path;
	int			counter;

	if (is_directory(cmd))
		exit(126);
	if (is_path(cmd) && access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path = find_env("PATH");
	if (!path)
		return (path_error(cmd), NULL);
	path_arr = ft_split(path, ':');
	counter = -1;
	while (path_arr[++counter])
	{
		search_path = ft_str_arr_join((char *[])
			{path_arr[counter], "/", cmd}, 3);
		if (access(search_path, F_OK) != 0)
			continue ;
		safe_free(path_arr);
		return (search_path);
	}
	return (path_error(cmd), NULL);
}
