
#include "../minishell.h"

int	pathfinder(t_data *d)
{
	char	**strs;

	strs = d->env;
	while (ft_strncmp("PATH", *strs, 4))
		strs++;
	if (*strs == NULL)
		return (1); //err a implemment
	d->paths = ft_split(*strs, ':');
	if (!d->paths)
		return (1); //err a implement
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
		return (1); //err a implement
	if (pathfinder(d))
		return (1); //err a implement
	return (0);
}

int	clean_data(t_data *d)
{
	int	i;

	i = -1;
	while (d->paths[++i])
		free(d->paths[i]);
	i = -1;
	while (d->env[++i])
		free(d->env[i]);
	free(d->paths);
	free(d->env);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (1); //malloc error a implement
	if (init_data(data, env))
		return (1);
	(void) av;
	if (ac != 1)
	{
		free(data);
		return (0);
	}
	shell_loop(data, env);
	clean_data(data);
	free(data);
	return (0);
}
