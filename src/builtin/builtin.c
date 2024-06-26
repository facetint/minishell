/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:04:26 by facetint          #+#    #+#             */
/*   Updated: 2024/04/02 17:34:38 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/env.h"

int	isbuiltin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	return (0);
}

void	execute_builtin(t_command *cmd, int fd[2])
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		builtin_echo(cmd, fd);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		builtin_export(cmd, fd);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		builtin_env(*get_env(), fd);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		builtin_exit(cmd);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		builtin_pwd(cmd);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		builtin_cd(cmd);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		builtin_unset(cmd, fd);
}
