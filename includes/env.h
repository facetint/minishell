#ifndef ENV_H
# define ENV_H

typedef struct s_envList
{
	char *key;
	char *value;
	struct s_envList *next;
} t_envList;

t_envList	*make_list(char **env);
void		print_list(t_envList *lst);
char		**make_arr(t_envList *lst);
void		print_env(char **env);
char		*strchr_new(const char *str, int c);
char		*strdup_n(char *str, char c);
int			lstsize(t_envList *lst);
void		builtin_env(t_envList *env);
t_envList	*get_global_env();

#endif
