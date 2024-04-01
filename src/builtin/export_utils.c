/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 15:35:28 by facetint          #+#    #+#             */
/*   Updated: 2024/04/01 15:39:21 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/env.h"
#include "../../includes/utils.h"
#include "../../memory-allocator/allocator.h"

void	set_export(t_list *env, t_list *node)
{
	t_list	*existing_node;

	existing_node = find_node(env, ((t_entry *)node->content)->key);
	if (!existing_node)
	{
		ft_lstadd_back(get_global_env(), node);
		return ;
	}
	safe_free(((t_entry *)existing_node->content)->key);
	safe_free(((t_entry *)existing_node->content)->value);
	safe_free(existing_node->content);
	existing_node->content = node->content;
	safe_free(node);
}

void	export_env(char *format)
{
	t_list	*node;

	node = to_node(format);
	if (!node)
		node = create_node(ft_strdup(format), ft_strdup(""));
	set_export(*get_global_env(), node);
}
