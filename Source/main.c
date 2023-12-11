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
=======
// int	get_env(t_data *d, char **env)
// {
// 	if (d->cmd == NULL)
// 		return (1);
// 	pathfinder(d->cmd, env);
// 	return (0);
// }

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
	d = malloc(sizeof(t_data));
	if (d == NULL)
		return (1); //malloc error a implement
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

>>>>>>> xavrestart
int	main(int ac, char **av, char **env)
{
	t_data	*data;
	char	**new_env;
	int i;

<<<<<<< HEAD
	i = 0;
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (0);
=======
	if (init_data(data, env))
		return (1);
>>>>>>> xavrestart
	(void) av;
	if (ac != 1)
	{
		free(data);
		return (0);
	}
	new_env = env_alloc(env);
	while (new_env[i])
	{
		printf("%s\n", new_env[i]);
		i++;
	}
	shell_loop(data, env);
	free(data);
	free(new_env);
	return (0);
}
