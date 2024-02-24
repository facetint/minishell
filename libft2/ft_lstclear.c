/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcoskun <hcoskun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:17:56 by hcoskun           #+#    #+#             */
/*   Updated: 2023/07/09 00:17:43 by hcoskun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;
	t_list	*tmp;

	if (!lst || !del)
		return ;
	node = *lst;
	while (node)
	{
		tmp = node;
		node = node -> next;
		ft_lstdelone(tmp, del);
	}
	*lst = NULL;
}
