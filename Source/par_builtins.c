/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:15:47 by maderuel          #+#    #+#             */
/*   Updated: 2024/01/22 15:31:09 by maderuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	par_ex_sub(t_data *d, int cc, int i)
{
	int		j;
	char	**tmp;

	j = -1;
	tmp = ft_split(d->cmd[cc].cmd_arg[i], '=');
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
	return (0);
}

int	check_inp(t_data *d, int cc, int i)
{
	if (ft_isdigit(d->cmd[cc].cmd_arg[i][0])
		|| !ft_isalpha(d->cmd[cc].cmd_arg[i][0]))
		return (ft_dprintf(2, "export: '%s' : not a valid identifier\n",
				d->cmd[cc].cmd_arg[i]), 1);
	return (0);
}

int	par_export(t_data *d, int cc)
{
	int		i;
	char	**tmp;

	i = 0;
	while (d->cmd[cc].cmd_arg[++i])
	{	
		if (check_inp(d, cc, i))
			return (g_ret = 1, 1);
		if (ft_strchr(d->cmd[cc].cmd_arg[i], '='))
		{
			tmp = ft_split(d->cmd[cc].cmd_arg[i], '=');
			if (find_var(d->env, tmp[0]))
				par_ex_sub(d, cc, i);
			else
			{
				d->env = ft_tabjoin(d->env, d->cmd[cc].cmd_arg[i]);
				if (!d->env)
					return (ft_dprintf
						(2, "Failed to malloc env after export\n"), 1);
			}
			clean_strs(tmp, 0, 0);
		}
	}
	return (0);
}

int	par_unset(t_data *d, int cc)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (d->cmd[cc].cmd_arg[++i])
	{
		j = -1;
		while (d->env[++j])
		{
			len = ft_strlen(d->env[j]) - ft_strlen(ft_strchr(d->env[j], '='));
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
