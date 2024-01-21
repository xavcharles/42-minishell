/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:30:48 by xacharle          #+#    #+#             */
/*   Updated: 2024/01/20 17:30:50 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*dol_qmark(void)
{
	char	*ret;

	ret = ft_itoa(g_ret);
	if (!ret)
		return (NULL);
	return (ret);
}

char	*double_dollar(void)
{
	char	*tmp;

	tmp = ft_strdup("$$");
	if (!tmp)
		return (NULL);
	return (tmp);
}

char	*env_varval(t_data *d, char *str)
{
	int		i;
	int		len;
	char	*tmp;

	i = -1;
	if (!ft_strncmp(str, "?", ft_strlen(str)))
		return (dol_qmark());
	if (!ft_strncmp(str, "$$", 2))
		return (double_dollar());
	while (d->env[++i])
	{
		if (!ft_strncmp(d->env[i], str, ft_strlen(str)))
		{
			if (ft_strchr(d->env[i], '='))
			{
				len = ft_strlen(ft_strchr(d->env[i], '=') - 1);
				tmp = ft_substr(d->env[i], ft_strlen(str) + 1, len);
				if (!tmp)
					return (NULL);
				return (tmp);
			}
		}
	}
	return (NULL);
}

int	ven_larlav(t_data *d, char *str)
{
	int	i;

	i = 0;
	if (!ft_strncmp(str, "?", ft_strlen(str)))
		return (ft_nbsize(g_ret));
	if (!ft_strncmp(str, "$$", 2))
		return (ft_strlen(str) + 1);
	while (d->env[i])
	{
		if (!ft_strncmp(d->env[i], str, ft_strlen(str)))
		{
			if (!ft_strchr(d->env[i], '='))
				return (0);
			else
				return (ft_strlen(ft_strchr(d->env[i], '=')) - 1);
		}
		i++;
	}
	return (0);
}

int	len_varval(t_data *d, char *str, int op)
{
	int	i;

	i = 0;
	if (!ft_strncmp(str, "?", ft_strlen(str)))
		return (ft_nbsize(g_ret));
	if (!ft_strncmp(str, "$", 1))
		return (ft_strlen(str) + op);
	while (d->env[i])
	{
		if (!ft_strncmp(d->env[i], str, ft_strlen(str)))
		{
			if (!ft_strchr(d->env[i], '='))
				return (0);
			else
				return (ft_strlen(ft_strchr(d->env[i], '=')) - 1);
		}
		i++;
	}
	return (0);
}
