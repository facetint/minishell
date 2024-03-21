/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmanurcetintas <fatmanurcetintas@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:04:14 by facetint          #+#    #+#             */
/*   Updated: 2024/03/22 00:35:41 by fatmanurcet      ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include "../../libft/libft.h"
#include "stdbool.h"

static  bool is_numeric(char *s)
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
    int     exit_status;

    exit_status = 0;
    if (!(cmd->args[1]))
    {
        ft_putstr_fd("exit\n", 1);
        exit(EXIT_SUCCESS);
    }
    status = is_numeric((cmd->args[1]));
    if (status == false)
    {
        ft_putstr_fd("exit\n", 1);
        printf("minishell: exit: %s: numeric argument required\n", cmd->args[1]);
        exit_status = 255;
    }
    else if (!cmd->args[2] && status == true)
        exit_status = ft_atoi((cmd->args[1]));
    else if (cmd->args[2])
    {
        ft_putstr_fd("exit\n", 1);
        ft_putstr_fd("minishell: exit: too many arguments\n", 2);
        *get_exit_status() = 1;
        return ;
    }
    *get_exit_status() = exit_status;
    exit(exit_status);
}
