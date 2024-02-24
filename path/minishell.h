/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:19:16 by facetint          #+#    #+#             */
/*   Updated: 2023/12/21 11:55:13 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H
 
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <signal.h>
# include <sys/wait.h>

typedef struct s_env
{
	char			*key;
	char			*value;
}					t_env;

typedef struct s_shell
{
    t_list  *env;
    char    *cmd;
    char    *file;
}              t_shell;

int     init_env(t_shell **mini_shell);
void    get_env(char **env, t_shell **mini_shell);
void    ft_split_free(char **str);
void    signal_(void);
void    ft_handler(int signum);
#endif