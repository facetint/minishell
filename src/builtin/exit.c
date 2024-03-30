/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:04:14 by facetint          #+#    #+#             */
/*   Updated: 2024/03/30 15:44:22 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>
#include "../../libft/libft.h"
#include "stdbool.h"
#include "../../includes/env.h"

static bool	is_numeric(char *s)
{
	while ((9 <= *s && *s <= 13) || *s == 32)
		s++;
	if (*s == 43 || *s == 45)
		s++;
	while (48 <= *s && *s <= 57)
		s++;
	while ((9 <= *s && *s <= 13) || *s == 32)
		s++;
	if (*s != '\0')
		return (false);
	return (true);
}

void	exit_numeric_error(t_command *cmd)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(cmd->args[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	*get_exit_status() = 255;
}

void	builtin_exit(t_command *cmd)
{
	bool	status;
	int		exit_status;

	exit_status = 0;
	if (!(cmd->args[1]))
	{
		abort_function();
		exit(EXIT_SUCCESS);
	}
	status = is_numeric((cmd->args[1]));
	if (status == false)
	{
		exit_numeric_error(cmd);
		exit_status = 255;
	}
	else if (!cmd->args[2] && status == true)
		exit_status = ft_atoi((cmd->args[1]));
	else if (cmd->args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		*get_exit_status() = 1;
		return ;
	}
	*get_exit_status() = exit_status;
	exit(exit_status);
}
