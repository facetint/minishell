/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:41:06 by facetint          #+#    #+#             */
/*   Updated: 2024/03/28 17:25:28 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>
#include <stdio.h>
#include "../../memory-allocator/allocator.h"

void	builtin_pwd(t_command *cmd)
{
	char	*path;

	(void)cmd;
	path = safe_malloc(sizeof(char) * 4097);
	getcwd(path, 4097);
	printf("%s\n", path);
	safe_free(path);
}
