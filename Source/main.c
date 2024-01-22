/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:43:02 by maderuel          #+#    #+#             */
/*   Updated: 2024/01/22 17:21:04 by maderuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_ret;

int	wipe_data(t_data *data)
{
	if (data->paths)
		clean_strs(data->paths, 0, 0);
	if (data->env)
		clean_strs(data->env, 0, 0);
	if (data->pwd)
		free(data->pwd);
	close(data->std_in);
	close(data->std_out);
	free(data);
	return (0);
}

int	pathfinder(t_data *d)
{
	char	**strs;

	strs = d->env;
	while (*strs)
	{
		if (!ft_strncmp(*strs, "PATH", 4))
		{
			d->paths = ft_split(*strs, ':');
			if (!d->paths)
				return (ft_dprintf
					(2, "Minishell: failed to malloc in pathfinder function\n"));
			return (0);
		}
		strs++;
	}
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
	d->std_out = dup(1);
	d->std_in = dup(0);
	d->prev = 0;
	d->hd = NULL;
	d->nb_heredoc = 0;
	if (env_cpy(d, env))
		return (g_ret = 2, 1);
	if (pathfinder(d))
		return (g_ret = 2, 1);
	m_get_pwd(d);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	if (isatty(STDIN_FILENO) == 0)
		return (1);
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (ft_dprintf(2, "Minishell: failed to malloc data structure\n"));
	if (init_data(data, env))
		return ((wipe_data(data)), 1);
	(void) av;
	if (ac != 1)
	{
		free(data);
		return (0);
	}
	shell_loop(data);
	wipe_data(data);
	return (0);
}
