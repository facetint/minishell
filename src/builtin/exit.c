/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:04:14 by facetint          #+#    #+#             */
/*   Updated: 2024/03/16 18:45:30 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include "../../memory-allocator/allocator.h"
#include <unistd.h>
#include <stdlib.h>
#include "../../libft/libft.h"
#include "stdbool.h"

static bool    is_numeric(char *s)
{
    while ((9 <= *s && *s <= 13) || *s == 32)
        s++;
    if (*s == 43 || *s == 45)
        s++;
    while (48 <= *s && *s <= 57)
        s++;
    while ((9 <= *s && *s <= 13) || *s == 32)
        s++;
    if (*s != '\0')
        return (false);
    return (true);
}
void    builtin_exit(t_command *cmd)
{
    bool    status;
    int     exit_value;

    exit_value = 0;
    if (!(cmd->args[1]))
        exit(EXIT_SUCCESS);
    status = is_numeric((cmd->args[1]));
    if (status == false)
    {
        printf("bash: %s: numeric argument required\n",
            cmd->args[0]);
        exit_value = 255;
    }
    else if (status == true && !(cmd->args[1]))
        exit_value = ft_atoi((cmd->args[0]));
    else
    {
        printf("bash: exit: too many arguments\n");
        *get_exit_status() = 1;
        return ;
    }
    exit(exit_value);
}
