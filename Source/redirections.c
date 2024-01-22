/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:28:49 by maderuel          #+#    #+#             */
/*   Updated: 2024/01/22 16:33:06 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_pipe(t_data *d, char *delim)
{
	int	j;

	j = 0;
	while (j < d->nb_heredoc)
	{
		if (!ft_strcmp(d->hd[j].delim, delim))
			return (d->hd[j].fd[0]);
		j++;
	}
	return (-1);
}

void	dup_if_out(int fd, char *sign, char **tmp)
{
	if ((!ft_strcmp(sign, ">")) || (!ft_strcmp(sign, ">>")))
		dup2(fd, 1);
	else
		dup2(fd, 0);
	close(fd);
	clean_strs(tmp, 0, 0);
}

int	redir_all(t_data *d, int cc)
{
	char	**tmp;
	int		i;
	int		fd;

	i = -1;
	if (!d->cmd[cc].all)
		return (1);
	while (d->cmd[cc].all[++i])
	{
		tmp = ft_split(d->cmd[cc].all[i], ' ');
		if (!tmp)
			return (1);
		if (!ft_strcmp(tmp[0], ">"))
			fd = open(tmp[1], O_CREAT | O_TRUNC | O_RDWR, 0666);
		else if (!ft_strcmp(tmp[0], ">>"))
			fd = open(tmp[1], O_CREAT | O_APPEND | O_RDWR, 0666);
		else if (!ft_strcmp(tmp[0], "<"))
			fd = open(tmp[1], O_RDONLY);
		else if (!ft_strcmp(tmp[0], "<<"))
			fd = get_pipe(d, tmp[1]);
		if (fd < 0)
			return (clean_strs(tmp, 0, 0), perror("file not found\n"), 1);
		dup_if_out(fd, tmp[0], tmp);
	}
	return (0);
}
