/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:23:50 by maderuel          #+#    #+#             */
/*   Updated: 2024/01/22 12:44:05 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
int	fd_manager(t_pipe p, t_data *d, int cc)
{
	(void) cc;
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

	if (pipe(p.end) == -1)
		return (1);
	pid = fork();
	if (pid < 0)
		return (printf("fork err") * 0);
	if (pid == 0)
	{
		fd_manager(p, d, cc);
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
*/
