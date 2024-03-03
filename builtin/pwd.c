/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcoskun <hcoskun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:builtin/pwd.c
/*   Created: 2024/03/02 13:41:06 by facetint          #+#    #+#             */
/*   Updated: 2024/03/03 13:17:22 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>
=======
/*   Created: 2023/06/24 20:30:45 by hcoskun42         #+#    #+#             */
/*   Updated: 2023/12/31 15:40:54 by hcoskun42        ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
>>>>>>> main:libft/ft_calloc.c
#include "../memory-allocator/allocator.h"

void    builtin_pwd(t_command *cmd)
{
    (void)cmd;
    char    *path;
    
    path = safe_malloc(sizeof(char) * 4097);
	getcwd(path, 4097);
	printf("%s\n", path);
	safe_free(path);
}
