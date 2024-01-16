
#include "../minishell.h"

int trim_squote(char **cmd_arg, int j)
{
	char	*tmp;

	tmp = ft_strtrim(cmd_arg[j], " \t");
	if (!tmp)
		return (1);
	free(cmd_arg[j]);
	cmd_arg[j] = ft_strdup(tmp);
	free(tmp);
	if (!cmd_arg[j])
		return (1);
	return (0);
}

int trim_dquote(char **cmd_arg, int j)
{
	char	*tmp;

	tmp = ft_strtrim(cmd_arg[j], " \t");
	if (!tmp)
		return (1);
	free(cmd_arg[j]);
	cmd_arg[j] = ft_strdup(tmp);
	free(tmp);
	if (!cmd_arg[j])
		return (1);
	return (0);
}

int	trim_args(t_data *d)
{
	int	i;
	int	j;
	char	*tmp;

	i = -1;
	while (++i < d->cmd_count)
	{
		if (d->cmd[i].cmd)
		{
			j = -1;
			while (d->cmd[i].cmd_arg[++j])
			{
				if (d->cmd[i].cmd_arg[j][0] == '"')
				{
					tmp = ft_strtrim(d->cmd[i].cmd_arg[j], " \t");
					if (!tmp)
						return (1);
					free(d->cmd[i].cmd_arg[j]);
					d->cmd[i].cmd_arg[j] = ft_strdup(tmp);
					free(tmp);
					if (!d->cmd[i].cmd_arg[j])
						return (1);
				}
			}
		}
	}
	return (0);
}
