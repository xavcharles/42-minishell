/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maderuel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:24:51 by maderuel          #+#    #+#             */
/*   Updated: 2024/01/15 16:43:06 by maderuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **ft_tabjoin(char **tab, char *s)
{
	int i;
	int j;
	char **n_tab;

	i = 0;
	j = 0;
	(void) s;
	while (tab[i])
		i++;
	n_tab = malloc(sizeof(char *) * (i + 2));
	if (n_tab == NULL)
		return (NULL);
	while (j < i)
	{
		n_tab[j] = ft_strdup(tab[j]);
		free(tab[j]);
		j++;
	}
	free(tab);
	n_tab[j] = ft_strdup(s);
	n_tab[j + 1] = NULL;
	return (n_tab);
}

int	sub_export(t_data *d, int i, int cc)
{
	int		j;
	char	**tmp;

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
					return (ft_exit(d, 1), 1);
				}
			}
		}
	}
	return (0);
}

int	ft_export(t_data *d, int cc)
{
	int		i;
	int		j;
	char **tmp;

	i = 0;
	while (d->cmd[cc].cmd_arg[++i])
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
						return (ft_exit(d, 1), 1);
					}
				}
			}
		}
		else
		{
			d->env = ft_tabjoin(d->env, d->cmd[cc].cmd_arg[i]);
			if (!d->env)
				return(ft_exit(d, 1), printf("Failed to malloc env after export\n"));
		}
			clean_strs(tmp, 0, 0);
	}
	return (ft_exit(d, 0), 0);
}

char	**ft_subtab(char **tab, char *s)
{
	int		i;
	int		j;
	char	**n_tab;

	n_tab = malloc(sizeof(char *) * strs_len(tab));
	if (!n_tab)
		return (printf("malloc error in subtab\n"), NULL);
	i = -1;
	j = 0;
	while (tab[++i])
	{
		if (ft_strncmp(tab[i], s, ft_strlen(s)))
		{
			n_tab[i - j] = ft_strdup(tab[i]);
			if (!n_tab[i - j])
				return (printf("malloc error in subtab\n"), NULL);
		}
		else
			j++;
	}
	n_tab[i - j] = NULL;
	clean_strs(tab, 0, 0);
	return (n_tab);
}

int	ft_unset(t_data *d, int cc)
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
					return (ft_exit(d, 1), 1);
				break ;
			}
		}
	}
	return (ft_exit(d, 0), 0);
}
