/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 09:27:13 by hamza             #+#    #+#             */
/*   Updated: 2024/04/02 17:01:45 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../libft/libft.h"

typedef struct s_entry
{
	char	*key;
	char	*value;
}	t_entry;

t_list		*to_node(char *env);
t_list		*to_list(char **env);
char		**to_arr(t_list *lst);
void		builtin_env(t_list *env, int fd[2]);
t_list		**get_global_env(void);
char		*ft_unsafe_substr(char const *s, unsigned int start, size_t len);
t_list		*create_node(char *key, char *value);
void		free_list(t_list *lst);
char		*find_env(char *key);
void		unset_env(char *varname);
t_list		*find_node(t_list *env, char *key);

#endif
