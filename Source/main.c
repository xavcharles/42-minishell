/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maderuel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:43:02 by maderuel          #+#    #+#             */
/*   Updated: 2023/12/05 13:46:35 by maderuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

<<<<<<< HEAD
<<<<<<< HEAD
=======
// int	get_env(t_data *d, char **env)
// {
// 	if (d->cmd == NULL)
// 		return (1);
// 	pathfinder(d->cmd, env);
// 	return (0);
// }

=======
>>>>>>> xavrestart
int	pathfinder(t_data *d)
{
	char	**strs;

	strs = d->env;
	while (ft_strncmp("PATH", *strs, 4))
		strs++;
	if (*strs == NULL)
		return (1); //err a implemment
	d->paths = ft_split(*strs, ':');
	if (!d->paths)
		return (1); //err a implement
	return (0);
}

int	init_data(t_data *d, char **env)
{
	d->cmd = NULL;
	d->cmds = NULL;
	d->seps = NULL;
	d->cmd_count = 0;
	d->sep_count = 0;
	d->err = 0;
	d->p = NULL;
	if (env_cpy(d, env))
		return (1); //err a implement
	if (pathfinder(d))
		return (1); //err a implement
	return (0);
}

