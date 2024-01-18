/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maderuel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:23:50 by maderuel          #+#    #+#             */
/*   Updated: 2024/01/18 17:39:07 by maderuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fd_manager(t_pipe p, t_data *d)
{
	close(p.end[0]);
	dup2(p.end[1], 1);
	close(p.end[1]);
	close(d->std_in);
	close(d->std_out);
	return (0);
}

int	ft_pipe(t_data *d, int cc)
{
	t_pipe	p;
	pid_t	pid;

	pipe(p.end);
	pid = fork();
	if (pid < 0)
		return (printf("fork err") * 0);
	if (pid == 0)
	{
		fd_manager(p, d);
		exec_1(d, cc);
	}
	else
	{
		close(p.end[1]);
		dup2(p.end[0], 0);
		close(p.end[0]);
	}
	return (0);
}
