
#include "../minishell.h"

char	*dol_qmark()
{
	char	*ret;

	ret = ft_itoa(g_ret);
	if (!ret)
		return (NULL);
	return (ret);
}

char	*env_varval(t_data *d, char *str)
{
	int	i;
	int	len;
	char	*tmp;

	i = 0;
	if (!ft_strncmp(str, "?", ft_strlen(str)))
		return (dol_qmark());
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
	if (!ft_strncmp(str, "?", ft_strlen(str)))
		return (ft_nbsize(g_ret));
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
