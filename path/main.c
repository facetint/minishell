/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facetint <facetint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:19:20 by facetint          #+#    #+#             */
/*   Updated: 2023/12/21 14:21:51 by facetint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strcmp(char *s1, char *s2)
{
	int i = 0;
	
	while(s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{	
		i++;
	}
	return (s1[i] - s2[i]);
}

int init_env(t_shell **mini_shell)
{
    *mini_shell = malloc(sizeof(t_shell));
    if(!mini_shell)
        return(1);
    (*mini_shell)->env = malloc(sizeof(t_list));
    if(!(*mini_shell)->env)
        return(1);
    return(0);
}

void ft_split_free(char **str)
{
    int i;

    i = 0;
    while(str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}


void get_env(char **env, t_shell **mini_shell)
{
    t_env *a;
    char **str;

    free((*mini_shell)->env);
    (*mini_shell)->env = NULL;
    
    while (*env)
	{
		a = malloc(sizeof(t_env));
		str = ft_split(*env, '=');
		if (!str)
			rerun (NULL);
		if (str && str[0] && str[1])
		{
			a->key = ft_strdup(str[0]);
			a->value = ft_strdup(str[1]);
			ft_lstadd_back(&(*mini_shell)->env, ft_lstnew(a));
		}
		ft_split_free(str);
		env++;
	}
}

char	*search_command(char *cmd, char **value)
{
	char	*content;
	char	*tmp;
	char	*new_str;
	int		index;

	tmp = *value;
	index = 0;
	(void)cmd;
	while (*tmp && *tmp != ':')
	{
		index++;
		tmp++;
	}
	if (!index)
		return (NULL);
	new_str = ft_substr(*value, 0, index);
	content = ft_strjoin(new_str, "/");
	free(new_str);
	new_str = ft_strjoin(content, cmd);
	free(content);
	if (*tmp)
		*value = *value + index + 1;
	return (new_str);
}

char	*_search_path(t_shell *m_shell)
{
	t_env	*env;
	t_list	*tmp;
    int     i;
	char	*value;

    i = -1;
	value = NULL;
	tmp = m_shell->env;
	while (tmp)
	{
		env = tmp->content;
		if (ft_strcmp(env->key, "PATH") == 0)
		{
			value = env->value;
			return (value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*search_path(t_shell *mini_shell)
{
	char    *tmp;
	char    *file;
	char    **full_path;
	int i;

	i = 0;
	if (mini_shell->cmd[0] == '.' || mini_shell->cmd[0] == '/')
	{
		if (access(mini_shell->cmd, X_OK) == 0)
			return(mini_shell->cmd);
		else
			return (NULL);
	}
	tmp = _search_path(mini_shell);
	full_path = ft_split(tmp, ':');
	while(full_path[i])
	{
		tmp = ft_strjoin(full_path[i], "/");
		file = ft_strjoin(tmp, mini_shell->cmd);
		free(tmp);
		if (access(file, X_OK) == 0)
		{
			ft_split_free(full_path);
			return(file);
		}
		i++;
		free(file);
	}
	return(NULL);
}

int main(int ac, char **av, char **env)
{
    t_shell *mini_shell;

    if(init_env(&mini_shell) == 1) 
        exit(1);
    get_env(env, &mini_shell);
    signal_();
    while (1)
    {
        mini_shell->cmd = readline("Minisheeeel\n");
        mini_shell->file = search_path(mini_shell);
		printf("file = %s\n",mini_shell->file);
    }
    return(0);
}