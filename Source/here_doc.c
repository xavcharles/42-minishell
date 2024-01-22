/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 21:58:27 by xacharle          #+#    #+#             */
/*   Updated: 2024/01/22 03:50:40 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	break_doc_loop(char *end, char *str)
{
	if (!str && g_ret != 130)
	{
		printf("minishell: warning: here-document delimited by end-of-file ");
		printf("(wanted `%s')\n", end);
		return (1);
	}
	if (g_ret == 130 || str == NULL || ft_strcmp(str, end) == 0)
	{
		free(str);
		return (1);
	}
	return (0);
}

int	nb_heredoc(t_data *d)
{
	int	i;
	int	j;
	int	total;

	total = 0;
	i = 0;
	while (i < d->cmd_count)
	{
		j = 0;
		if (d->cmd[i].all)
		{
			while (d->cmd[i].all[j])
			{
				if (!ft_strncmp(d->cmd[i].all[j], "<<", 2))
					total++;
				j++;
			}
		}
		i++;
	}
	return (total);
}

int	delim_heredoc(t_data *d)
{
	int	i;
	int	j;
	int	total;

	total = 0;
	i = -1;
	while (++i < d->cmd_count)
	{
		if (d->cmd[i].all)
		{
			j = -1;
			while (d->cmd[i].all[++j])
			{
				if (!ft_strncmp(d->cmd[i].all[j], "<<", 2))
				{
					d->hd[total].delim = ft_strdup(d->cmd[i].all[j] + 3);
					if (!d->hd[total].delim)
						return (1);
					if (pipe(d->hd[total++].fd) < 0)
						return (1);
				}
			}
		}
	}
	return (0);
}

void	do_heredoc(t_data *d, int i)
{
	char	*str;

	close(d->hd[i].fd[0]);
	close(d->std_in);
	close(d->std_out);
	while (1)
	{		
		ic_sigs(3);
		str = readline("here_doc $>");
		if (break_doc_loop(d->hd[i].delim, str))
			break ;
		ft_putstr_fd(str, d->hd[i].fd[1]);
		ft_putchar_fd('\n', d->hd[i].fd[1]);
		free(str);
	}
}

int	init_heredoc(t_data *d)
{
	pid_t	pid;
	int		i;

	d->nb_heredoc = nb_heredoc(d);
	if (!d->nb_heredoc)
		return (0);
	d->hd = malloc(sizeof(t_here) * d->nb_heredoc);
	if (!d->hd || delim_heredoc(d))
		return (1);
	pid = fork();
	i = 0;
	if (pid == 0)
	{
		while (i < d->nb_heredoc)
			do_heredoc(d, i++);
		ft_exit(d, 0, -1);
	}
	else
	{
		while (i < d->nb_heredoc)
			close(d->hd[i++].fd[1]);
		wait(NULL);
	}
	return (0);
}
