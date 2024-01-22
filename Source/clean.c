/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:31:25 by xacharle          #+#    #+#             */
/*   Updated: 2024/01/22 17:21:15 by maderuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clean_heredoc(t_data *d)
{
	int	i;

	i = 0;
	if (d->hd)
	{
		while (i < d->nb_heredoc)
		{
			if (d->hd[i].delim)
				free(d->hd[i].delim);
			close(d->hd[i].fd[0]);
			close(d->hd[i].fd[1]);
			i++;
		}
		free(d->hd);
	}
}

void	clean_strs(char **strs1, char **strs2, char **strs3)
{
	char	**strs;

	if (strs1)
	{
		strs = strs1;
		while (*strs)
			free(*(strs++));
		free(strs1);
	}
	if (strs2)
	{
		strs = strs2;
		while (*strs)
			free(*(strs++));
		free(strs2);
	}
	if (strs3)
	{
		strs = strs3;
		while (*strs)
			free(*(strs++));
		free(strs3);
	}
}

void	clean_ccmd(t_ccmd *ccmd)
{
	clean_strs(ccmd->cmd_arg, ccmd->all, NULL);
	if (ccmd->cmd)
		free(ccmd->cmd);
	if (ccmd->prev_op)
		free(ccmd->prev_op);
	if (ccmd->next_op)
		free(ccmd->next_op);
}

int	clean_data(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->cmd_count)
	{
		if (d->cmd + i)
			clean_ccmd(d->cmd + i);
		i++;
	}
	if (d->cmd)
		free(d->cmd);
	clean_strs(d->seps, d->cmds, 0);
	clean_heredoc(d);
	data_zero(d);
	return (0);
}
