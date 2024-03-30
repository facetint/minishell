/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmanurcetintas <fatmanurcetintas@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 21:44:15 by fatmanurcet       #+#    #+#             */
/*   Updated: 2024/03/30 21:46:15 by fatmanurcet      ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../libft/libft.h"

t_list	**get_global_env(void)
{
	static t_list	*env;

	env = NULL;
	return (&env);
}
