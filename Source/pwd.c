
#include "minishell.h"

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
		return (1);
	while (env[i])
	{
		if (!ft_strdup(data->env[i], env[i]))
		{
			clean_strs(0, 0, 0, data->env);
			return (1);
		}
		i++;
	}
	data->env[i] = NULL;
	return (0);
}

int get_pwd(t_cmd *cmd, char **env)
{
	int	i;

    i = 0;
	cmd->pwd = NULL;
	cmd->old_pwd = NULL;
    while (env[i])
	{
		if (!ft_strncmp(env[i], "PWD", 3))
		{

		}
	}
}