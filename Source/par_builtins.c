
#include "../minishell.h"

int par_cd(t_data *d, int cc)
{
    char *dir;

	dir = d->cmd[cc].cmd_arg[1];
	if (chdir(dir) == 0)
		return (EXIT_SUCCESS);
	perror(dir);
	return (EXIT_FAILURE);
}

int par_export(t_data *d, int cc)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	while (d->cmd[cc].cmd_arg[++i])
	{
		if (ft_strchr(d->cmd[cc].cmd_arg[i], '='))
		{
			tmp = ft_split(d->cmd[cc].cmd_arg[i], '=');
			if (find_var(d->env, tmp[0]))
			{
				j = -1;
				while (d->env[++j])
				{
					if (!ft_strncmp(d->env[j], tmp[0], ft_strlen(tmp[0])))
					{
						free(d->env[j]);
						d->env[j] = ft_strdup(d->cmd[cc].cmd_arg[i]);
						if (!d->env[j])
						{
							clean_strs(tmp, 0, 0);
							return (1);
						}
					}
				}
			}
			else
			{
				d->env = ft_tabjoin(d->env, d->cmd[cc].cmd_arg[i]);
				if (!d->env)
					return(printf("Failed to malloc env after export\n"), 1);
			}
			clean_strs(tmp, 0, 0);
		}
	}
	return (0);
}

int par_unset(t_data *d, int cc)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (d->cmd[cc].cmd_arg[++i])
	{
		j = -1;
		len = ft_strlen(d->cmd[cc].cmd_arg[i]);
		while (d->env[++j])
		{
			if (!ft_strncmp(d->env[j], d->cmd[cc].cmd_arg[i], len))
			{
				d->env = ft_subtab(d->env, d->cmd[cc].cmd_arg[i]);
				if (!d->env)
					return (1);
				break ;
			}
		}
	}
	return (0);
}
