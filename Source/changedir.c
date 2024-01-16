/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changedir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maderuel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:24:21 by maderuel          #+#    #+#             */
/*   Updated: 2024/01/15 14:24:32 by maderuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	modif_dir(t_data *d, int cc)
{
	int	i;
	int j;

	i = -1;
	j = -1;
	while (d->env[++i])
		if (!ft_strncmp(d->env[i], "OLDPWD", 6))
			break;
	while (d->env[++j])
		if (!ft_strncmp(d->env[i], "PWD", 3))
			break;
	free(d->env[i]);
	d->env[i] = ft_strdup(d->env[j]);
	free(d->env[j]);
	d->env[j] = ft_strjoin(d->env[i], "/");
	d->env[j] = ft_strjoin(d->env[j], d->cmd[cc].cmd_arg[1]);
	return (1);
}

int	cd_builtin(t_data *d, int cc)
{
	char	*dir;

	dir = d->cmd[cc].cmd_arg[1];
	printf("oui\n");
	if (chdir(dir) == 0)
	{
		modif_dir(d, cc);
		return (EXIT_SUCCESS);
	}
	perror(dir);
	return (EXIT_FAILURE);
}
