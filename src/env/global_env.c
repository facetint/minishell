#include "../../libft/libft.h"

t_list	**get_global_env()
{
	static	t_list *env = NULL;
	return (&env);
}
