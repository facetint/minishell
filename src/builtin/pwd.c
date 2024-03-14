/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:41:06 by facetint          #+#    #+#             */
/*   Updated: 2024/03/14 16:06:25 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include "../../memory-allocator/allocator.h"

void    builtin_pwd(t_command *cmd)
{
    (void)cmd;
    char    *path;
    
    path = safe_malloc(sizeof(char) * 4097);
	getcwd(path, 4097);
	printf("%s\n", path);
	safe_free(path);
}
