#include "../minishell.h"

void	*ft_magic(void *p)
{
	static void 	*save;

	if (p != NULL)
		save = p;
	return (save);
}
