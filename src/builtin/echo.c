/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 11:48:26 by facetint          #+#    #+#             */
/*   Updated: 2024/03/28 17:21:42 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

int	is_n_option(char *str)
{
	int	i;
	int	len;

	if (!str)
		return (0);
	len = ft_strlen(str);
	if (len < 2)
		return (0);
	if (str[0] != '-')
		return (0);
	i = 1;
	while (str[i] == 'n')
		i++;
	if (i == len)
		return (1);
	return (0);
}

void	builtin_echo(t_command *cmd, int fd[2])
{
	char	**args;
	int		i;
	int		n_option;

	args = &cmd->args[1];
	i = 0;
	n_option = 0;
	while (is_n_option(args[i]))
		i++;
	if (i > 0)
		n_option = 1;
	while (args[i])
	{
		ft_putstr_fd(args[i], fd[1]);
		if (args[i + 1] != NULL)
			ft_putstr_fd(" ", fd[1]);
		i++;
	}
	if (!n_option)
		ft_putstr_fd("\n", fd[1]);
}
