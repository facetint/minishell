/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 20:06:35 by facetint          #+#    #+#             */
/*   Updated: 2024/03/29 23:19:18 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../includes/env.h"

void	builtin_env(t_list *env, int fd[2])
{
	t_entry	*node;

	while (env)
	{
		node = env->content;
		if (node->value)
		{
			ft_putstr_fd(node->key, fd[1]);
			ft_putstr_fd("=", fd[1]);
			ft_putstr_fd(node->value, fd[1]);
			ft_putstr_fd("\n", fd[1]);
		}
		env = env->next;
	}
}
