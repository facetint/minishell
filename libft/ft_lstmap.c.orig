/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcoskun <hcoskun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:14:57 by hcoskun           #+#    #+#             */
/*   Updated: 2023/07/11 14:47:38 by hcoskun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_node;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	content = f(lst -> content);
	new_node = ft_lstnew(content);
	if (!new_node)
	{
		del(content);
		ft_lstclear(&new_node, del);
		return (NULL);
	}
	new_node -> next = ft_lstmap(lst -> next, f, del);
	return (new_node);
}
