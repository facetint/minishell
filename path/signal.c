/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:19:11 by facetint          #+#    #+#             */
/*   Updated: 2023/12/21 13:55:33 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_handler(int signum)
{
    if (signum == SIGINT)
    {
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    }
} 

void    signal_(void)
{
    //signal(SIGINT, ft_handler);
    signal(SIGQUIT, SIG_IGN);
}