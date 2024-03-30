/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcoskun <hcoskun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:46:34 by facetint          #+#    #+#             */
/*   Updated: 2024/03/30 14:29:11 by hcoskun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>
#include <sys/wait.h>
#include "../../libft/libft.h"
#include "../../memory-allocator/allocator.h"
#include "../../includes/env.h"
#include <stdio.h>

t_list	**get_global_env()
{
	static	t_list *env = NULL;
	return (&env);
}

int is_path(char *str)
{
	return ((str[0] == '.' && str[1] == '/') || str[0] == '/');
}

char    *find_path(char *cmd)
{
    char    *path;
    char    **path_arr;
    char    *search_path;
    int     counter;

    if (is_path(cmd) && access(cmd, F_OK) == 0)
        return (ft_strdup(cmd));
    path = find_env("PATH");
	if (!path)
		return NULL;
    path_arr = ft_split(path, ':');

    counter = 0;
    while (path_arr[counter])
    {
		search_path = ft_str_arr_join((char*[]) {path_arr[counter], "/", cmd}, 3);
		if (access(search_path, F_OK) == 0)
        {
            safe_free(path_arr);
            return (search_path);
        }
        counter++;
    }
    return (NULL);
}
