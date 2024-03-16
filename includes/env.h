#ifndef ENV_H
# define ENV_H

#include "../libft/libft.h"

typedef struct s_envList
{
	char *key;
	char *value;
} t_envList;

t_list		*to_list(char **env);
char		**to_arr(t_list *lst);
void		print_list(t_envList *lst);
void		print_env(char **env);
char		*strchr_new(const char *str, int c);
char		*strdup_n(char *str, char c);
void		builtin_env(t_list *env, int fd[2]);
t_list		*get_global_env();
char		*ft_unsafe_substr(char const *s, unsigned int start, size_t len);
t_list		*create_node(char *key, char *value);
void		free_list(t_list *lst);

#endif
