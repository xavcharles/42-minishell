#include "../minishell.h"

int	cd_builtin(t_data *d, int cc)
{
	char *dir;

	dir = d->cmd[cc].cmd_arg[1];
	if (chdir(dir) == 0)
		return (EXIT_SUCCESS);
	perror(dir);
	return (EXIT_FAILURE);
}
