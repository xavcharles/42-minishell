
#include "../minishell.h"

int	get_env(t_data *d, char **env)
{
	if (d->cmd == NULL)
		return (1);
	pathfinder(d->cmd, env);
	return (0);
}

t_data	*init_data(t_data *d, char **env)
{
	get_env(d, env);
	return (d);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (0);
	(void) av;
	if (ac != 1)
	{
		free(data);
		return (0);
	}
	shell_loop(data, env);
	free(data);
	return (0);
}
