/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maderuel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:24:51 by maderuel          #+#    #+#             */
/*   Updated: 2024/01/15 14:25:10 by maderuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_var(char **env, char *var)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, ft_strlen(var)))
			return (1);
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
		return (printf("Minishell: failed to malloc in env_cpy\n"));
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
		return (printf("Minishell: failed to malloc in env_cpy\n"));
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
	int		i;
	char	**tmp;

	i = -1;
	(void) cc;
	while (d->env[++i])
	{
		if (!ft_strncmp(d->env[i], "PWD", 3))
		{
			tmp = ft_split(d->env[i], '=');
			write(1, tmp[1], ft_strlen(tmp[1]));
			write(1, "\n", 1);
			clean_strs(tmp, 0, 0);
			return (ft_exit(d, 0), EXIT_SUCCESS);
		}
	}
	return (ft_exit(d, 1), EXIT_FAILURE);
}
