/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:24:51 by maderuel          #+#    #+#             */
/*   Updated: 2024/01/22 16:23:40 by maderuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_var(char **env, char *var)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
		{
			j = ft_strlen(env[i]) - ft_strlen(ft_strchr(env[i], '='));
			if (!ft_strncmp(env[i], var, j))
				return (1);
		}
		else
		{
			if (!ft_strncmp(env[i], var, ft_strlen(env[i])))
				return (1);
		}
		i++;
	}
	return (0);
}

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

int	add_to_env(t_data *d, char *str, int i)
{
	char	*s;
	char	*n;

	if (!ft_strncmp(str, "SHLVL=", 6))
	{
		s = ft_substr(str, 0, 6);
		if (!s)
			return (1);
		n = ft_itoa(ft_atoi(str + 6) + 1);
		if (!n)
			return (free(s), 1);
		s = gnl_strjoin(s, n);
		if (!s)
			return (free(n), 1);
		d->env[i] = s;
		free(n);
	}
	else
		d->env[i] = ft_strdup(str);
	if (!d->env[i])
	{
		return (ft_dprintf(2, "Minishell: failed to malloc in env_cpy\n"));
	}
	return (0);
}

int	env_cpy(t_data *data, char **env)
{
	int		i;

	i = 0;
	if (find_var(env, "SHLVL"))
		data->env = malloc(sizeof(char **) * (strs_len(env) + 1));
	else
		data->env = malloc(sizeof(char **) * (strs_len(env) + 2));
	if (!data->env)
		return (ft_dprintf(2, "Minishell: failed to malloc in env_cpy\n"));
	while (env[i])
	{
		if (add_to_env(data, env[i], i))
			return (clean_strs(data->env, 0, 0), 1);
		i++;
	}
	if (!find_var(env, "SHLVL"))
	{
		if (add_to_env(data, "SHLVL=0", i))
			return (clean_strs(data->env, 0, 0), 1);
		data->env[i + 1] = NULL;
	}
	else
		data->env[i] = NULL;
	return (0);
}

int	pwd_builtin(t_data *d, int cc)
{
	(void) cc;
	printf("%s\n", d->pwd);
	return (0);
}
