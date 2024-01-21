/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 21:58:27 by xacharle          #+#    #+#             */
/*   Updated: 2024/01/22 00:03:38 by xacharle         ###   ########.fr       */
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

int     nb_heredoc(t_data *d)
{
    int i;
    
    int j;
    int total;
    
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

void delim_heredoc(t_data *d)
{
    int i;
    
    int j;
    int total;
    
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
				{
					d->hd[total].delim = ft_strdup(d->cmd[i].all[j] + 3);
					pipe(d->hd[total++].fd);
				}
				j++;
			}
		}
        i++;
    }
}

void	do_heredoc(t_data *d, int i)
{
	char *str;
	close (d->hd[i].fd[0]);
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

void    init_heredoc(t_data *d)
{
    pid_t   pid;
    int     i;

    d->nb_heredoc = nb_heredoc(d);
	if (!d->nb_heredoc)
		return ;
    d->hd = malloc(sizeof(t_here) * d->nb_heredoc);
    delim_heredoc(d);
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
}