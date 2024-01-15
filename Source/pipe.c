/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maderuel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:23:50 by maderuel          #+#    #+#             */
/*   Updated: 2024/01/15 14:23:53 by maderuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		close(p.end[0]);
		dup2(p.end[1], 1);
		if (!is_builtin(d, cc))
			if (exec_1(d, cc))
				return (printf("exec in piepe error\n"), 0);
	}
	else
	{
		wait(NULL);
		close(p.end[1]);
		dup2(p.end[0], 0);
	}
	return (0);
}
