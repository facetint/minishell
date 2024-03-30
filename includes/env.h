#ifndef ENV_H
# define ENV_H

#include "../libft/libft.h"

typedef struct s_entry
{
	char *key;
	char *value;
} t_entry;

t_list  *to_node(char *env);
t_list		*to_list(char **env);
char		**to_arr(t_list *lst);
void		print_list(t_entry *lst);
void		print_env(char **env);
char		*strchr_new(const char *str, int c);
char		*strdup_n(char *str, char c);
void		builtin_env(t_list *env, int fd[2]);
t_list		**get_global_env();
char		*ft_unsafe_substr(char const *s, unsigned int start, size_t len);
t_list		*create_node(char *key, char *value);
void		free_list(t_list *lst);
char		*find_env(char *key);
void		unset_env(char *varname);
t_list		*find_node(t_list *env, char *key);
#endif
