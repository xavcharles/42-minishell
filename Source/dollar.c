
#include "../minishell.h"

char	*env_varval(t_data *d, char *str)
{
	int	i;
	int	len;
	char	*tmp;

	i = 0;
	while (d->env[i])
	{
		if (!ft_strncmp(d->env[i], str, ft_strlen(str)))
		{
			if (!ft_strchr(d->env[i], '='))
				return (NULL);
			else
			{
				len = ft_strlen(ft_strchr(d->env[i], '=') - 1);
				tmp = ft_substr(d->env[i], ft_strlen(str) + 1, len);
				if (!tmp)
					return (NULL);
				return (tmp);
			}
		}
		i++;
	}
	return (NULL);
}

int	len_varval(t_data *d, char *str)
{
	int	i;

	i = 0;
	while (d->env[i])
	{
		if (!ft_strncmp(d->env[i], str, ft_strlen(str)))
		{
			if (!ft_strchr(d->env[i], '='))
				return (0);
			else
				return (ft_strlen(ft_strchr(d->env[i], '=') - 1));
		}
		i++;
	}
	return (0);
}
int	dollar_replace(t_data *d, char **cmdarg)
{
	int	i;
	int	len;
	char	*str;
	char	*tmp;
	char	*val;

	i = 0;
	str = ft_strchr(*cmdarg, '$');
	tmp = NULL;
	while (str[++i] && str[i] != ' ' && str[i] != '\t')
	{
		if (tmp)
			free(tmp);
		tmp = ft_substr(str + 1, 0, i);
		if (!tmp)
			return (1);
		printf("i = %d, tmp = %s\n", i, tmp);
		if (find_var(d->env, tmp))
			break ;
	}
	len = ft_strlen(*cmdarg) - ft_strlen(tmp) + len_varval(d, tmp);
	val = env_varval(d, tmp);
	if (!val && len_varval(d, tmp) != 0)
		return (free(tmp), 1);
	printf("len = %d\n %zu, %zu, %d\n", len, ft_strlen(*cmdarg), ft_strlen(tmp), len_varval(d, tmp));
	str = ft_calloc(len, sizeof(char*));
	if (!str)
	{
		if (val)
			free(val);
		return (free(tmp), 1);
	}
	i = ft_strlen(*cmdarg) - ft_strlen(ft_strchr(*cmdarg, '$'));
	ft_strlcat(str, *cmdarg, i + 1);
	i += len_varval(d, tmp);
	if (val)
		ft_strlcat(str, val, i + 1);
	i += ft_strlen(ft_strchr(*cmdarg, '$')) - ft_strlen(tmp) - 1;
	ft_strlcat(str, ft_strchr(*cmdarg, '$') + ft_strlen(tmp) + 1, i + 1);
	if (val)
		free(val);
	free(tmp);
	free(*cmdarg);
	*cmdarg = str;
	return (0);
}

int	dollar_search(t_data *d)
{
	int	i;
	int	j;
	char	*tmp;

	i = -1;
	while (++i < d->cmd_count)
	{
		if (d->cmd[i].cmd)
		{
			if (d->cmd[i].cmd == '"')
			{
				tmp = ft_strtrim(d->cmd[i], "\"");
				if (!tmp)
					return (1);
				if (ft_strchr(d->cmd[i], '$'))
				{
					if (dollar_replace(d, &tmp))
						return (1);
				}
				free(d->cmd[i]);
				free(d->cmd[i].cmd_arg[j]);
				d->cmd[i].cmd_arg[j] = ft_strdup(tmp);
				if (!d->cmd[i].cmd_arg[j])
					return (free(tmp), 1);
				d->cmd[i] = ft_strdup(tmp);
				if (!d->cmd[i])
					return (free(tmp), 1);
				free(tmp);
			}
			j = 0;
			while (d->cmd[i].cmd_arg[++j])
			{
				if (d->cmd[i].cmd_arg[j][0] == '"')
				{
					tmp = ft_strtrim(d->cmd[i].cmd_arg[j], "\"");
					if (!tmp)
						return (1);
					if (ft_strchr(d->cmd[i].cmd_arg[j], '$'))
					{
						if (dollar_replace(d, &tmp))
							return (1);
					}
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
