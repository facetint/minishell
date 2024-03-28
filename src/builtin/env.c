/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 20:06:35 by facetint          #+#    #+#             */
/*   Updated: 2024/03/28 14:56:11 by facetint         ###   ########.fr       */
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
		ft_putstr_fd(node->key, fd[1]);
		ft_putstr_fd("=", fd[1]);
		ft_putstr_fd(node->value, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		env = env->next;
	}
}
