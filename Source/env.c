/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maderuel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:24:51 by maderuel          #+#    #+#             */
/*   Updated: 2023/12/05 16:02:43 by maderuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_env(t_data *d)
{
	int i;

	i = -1;
	while (d->env[++i])
		printf("%s\n", d->env[i]);
	return (0);
}

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
	n_tab[j] = ft_strdup(s);
	n_tab[j + 1] = NULL;
	return (n_tab);
}

void	write_data_fd(t_data *d)
{
	int	i;
	int	l;

	i = 0;
	l = 0;
	while (d->env[i])
	{
		l = ft_strlen(d->env[i]) + 1;
		write(d->p->end[1], d->env[i], l);
	}
	write(d->p->end[1], "", 1);
}

int	ft_export(t_data *d)
{
	int		i;
	int		j;
	char **tmp;

	i = 0;
	j = 0;
	tmp = ft_split(d->cmd->cmd_arg[1], '=');
	while (d->env[i])
	{
		if (!ft_strncmp(tmp[0], d->env[i], ft_strlen(tmp[0])))
			j = i;
		i++;
	}
	if (j == 0)
		d->env = ft_tabjoin(d->env, d->cmd->cmd_arg[1]);
	else
		d->env[j] = ft_strjoin(d->env[j], tmp[1]);
	write_data_fd(d);
	return (0);
}

char	**ft_subtab(char **tab, char *s)
{
	int	i;
	int	j;
	char **n_tab;

	i = 0;
	j = 0;
	while (tab[i])
		i++;
	n_tab = malloc(sizeof(char *) * i);
	i = 0;
	while (tab[j + 1])
	{
		if (!ft_strncmp(s, tab[i], ft_strlen(s)))
			i++;
		n_tab[j] = ft_strdup(tab[i]);
		free(tab[i]);
		i++;
		j++;
	}
	free(tab);
	return (n_tab);
}

int	ft_unset(t_data *d)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (d->env[i])
	{
		while (d->cmd->cmd_arg[++j])
		{
			if (!ft_strncmp(d->env[i], d->cmd->cmd_arg[j], ft_strlen(d->cmd->cmd_arg[j])))
			{
				d->env = ft_subtab(d->env, d->cmd->cmd_arg[j]);
				return (0);
			}
		}
		i++;
	}
	return (0);
}
/*
char	**env_alloc(char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * i);
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
			return (NULL);
		i++;
	}
	return (new_env);
}*/
