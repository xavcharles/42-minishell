
#include "../minishell.h"

int	pathfinder(t_data *d)
{
	char	**strs;

	strs = d->env;
	while (ft_strncmp("PATH", *strs, 4))
		strs++;
	if (*strs == NULL)
		return (printf("Minishell: PATH not found\n"));
	d->paths = ft_split(*strs, ':');
	if (!d->paths)
		return (printf("Minishell: failed to malloc in pathfinder function\n"));
	return (0);
}

int	init_data(t_data *d, char **env)
{
	d->cmd = NULL;
	d->cmds = NULL;
	d->seps = NULL;
	d->cmd_count = 0;
	d->sep_count = 0;
	d->err = 0;
	d->p = NULL;
	if (env_cpy(d, env))
		return (1);
	if (pathfinder(d))
		return (1);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (printf("Minishell: failed to malloc data structure\n"));
	if (init_data(data, env))
		return (1);
	(void) av;
	if (ac != 1)
	{
		free(data);
		return (0);
	}
	shell_loop(data);
	if (d->paths)
        clean_strs(d->paths, 0, 0);
    if (d->env)
        clean_strs(d->env, 0, 0);
	free(data);
	return (0);
}
