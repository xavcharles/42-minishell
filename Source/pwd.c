
#include "../minishell.h"

int	strs_len(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return (0);
	while (strs[i])
		i++;
	return (i);
}

int	env_cpy(t_data *data, char **env)
{
	int	i;

	i = 0;
	data->env = malloc(sizeof(char **) * (strs_len(env) + 1));
	if (!data->env)
		return (printf("Minishell: failed to malloc in env_cpy\n"));
	while (env[i])
	{
		data->env[i] = ft_strdup(env[i]);
		if (!data->env[i])
		{
			clean_strs(data->env, 0, 0);
			return (printf("Minishell: failed to malloc in env_cpy\n"));
		}
		i++;
	}
	data->env[i] = NULL;
	return (0);
}

int	pwd_builtin(t_data *d, int cc)
{
	int	i;
	char **tmp;

	i = -1;
	(void) cc;
	while (d->env[++i])
	{
		if (!ft_strncmp(d->env[i], "PWD", 3))
		{
			tmp = ft_split(d->env[i], '=');
			write(1, tmp[1], ft_strlen(tmp[1]));
			write(1, "\n", 1);
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}
