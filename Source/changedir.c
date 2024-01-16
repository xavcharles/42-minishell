/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changedir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maderuel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:24:21 by maderuel          #+#    #+#             */
/*   Updated: 2024/01/16 18:55:34 by maderuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_dir(t_data *d, int cc)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (d->env[++i])
		if (!ft_strncmp(d->env[i], "OLDPWD", 6))
			break ;
	while (d->env[++j])
		if (!ft_strncmp(d->env[j], "PWD", 3))
			break ;
	free(d->env[i]);
	d->env[i] = ft_strdup(d->env[j]);
	free(d->env[j]);
	d->env[j] = ft_strjoin(d->env[i], "/");
	d->env[j] = ft_strjoin(d->env[j], d->cmd[cc].cmd_arg[1]);
	return (1);
}

int	sub_dir(t_data *d, int cc)
{
	int	i;
	int	j;
	int	tmp;

	i = -1;
	j = -1;
	while (d->env[++i])
		if (!ft_strncmp(d->env[i], "OLDPWD", 6))
			break ;
	while (d->env[++j])
		if (!ft_strncmp(d->env[j], "PWD", 3))
			break ;
	free(d->env[i]);
	d->env[i] = ft_strdup(d->env[j]);
	free(d->env[j]);
	tmp = ft_strlen(d->env[i]) - ft_strlen(d->cmd[cc].cmd_arg[1]);
	d->env[j] = ft_substr(d->env[i], tmp, ft_strlen(d->cmd[cc].cmd_arg[1]));
	return (1);
}

int	cd_builtin(t_data *d, int cc)
{
	char	*dir;

	dir = d->cmd[cc].cmd_arg[1];
	if (chdir(dir) == 0)
	{
		if (!ft_strncmp(dir, "..", 2))
			sub_dir(d, cc);
		else
			add_dir(d, cc);
		return (EXIT_SUCCESS);
	}
	perror(dir);
	return (EXIT_FAILURE);
}
