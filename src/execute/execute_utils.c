/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:46:34 by facetint          #+#    #+#             */
/*   Updated: 2024/04/01 15:40:46 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>
#include <sys/wait.h>
#include "../../libft/libft.h"
#include "../../memory-allocator/allocator.h"
#include "../../includes/env.h"
#include "../../includes/utils.h"
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

char	*handle_executable_file(char *path)
{
	if (is_directory(path))
	{
		print_error(path, "is a directory");
		exit(126);
	}
	else if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == 0)
			return (ft_strdup(path));
		print_error(path, "Permission denied");
		exit(126);
	}
	print_error(path, "No such file or directory");
	exit(127);
}

char	*find_path(char *cmd)
{
	char		*path;
	char		**path_arr;
	char		*search_path;
	int			counter;

	if (is_path(cmd))
		return (handle_executable_file(cmd));
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
