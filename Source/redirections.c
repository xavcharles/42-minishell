/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:28:49 by maderuel          #+#    #+#             */
/*   Updated: 2024/01/22 03:55:23 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	get_doc(t_data *d, char *end, int *p_fd, char **strs)
// {
// 	char	*str;

// 	close(p_fd[0]);
// 	// close(d->std_in);
// 	// close(d->std_out);
// 	while (1)
// 	{		
// 		ic_sigs(3);
// 		str = readline("here_doc $>");
// 		if (break_doc_loop(end, str))
// 			break ;
// 		ft_putstr_fd(str, p_fd[1]);
// 		ft_putchar_fd('\n', p_fd[1]);
// 		free(str);
// 	}
// 	close(p_fd[1]);
// 	clean_strs(strs, 0, 0);
// 	(void) d;
// }

// void	last_hd(pid_t pid, int p_fd[2], int status)
// {
// 	close(p_fd[1]);
// 	waitpid(pid, &status, 0);
// 	dup2(p_fd[0], 0);
// 	close(p_fd[0]);
// 	g_ret = WEXITSTATUS(status);
// }

// int	here_doc(t_data *d, char **strs, int cc, int i)
// {
// 	int		p_fd[2];
// 	int		status;
// 	pid_t	pid;

// 	status = 0;
// 	if (pipe(p_fd) < 0)
// 		return (1);
// 	pid = fork();
// 	if (pid < 0)
// 		return (2);
// 	if (pid == 0)
// 	{
// 		get_doc(d, strs[1], p_fd, strs);
// 		ft_exit(d, g_ret, -1);
// 	}
// 	if (d->cmd[cc].in[i + 1] != NULL)
// 	{
// 		close(p_fd[1]);
// 		waitpid(pid, &status, 0);
// 		close(p_fd[0]);
// 	}
// 	else
// 		last_hd(pid, p_fd, status);
// 	return (0);
// }

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
		if (!tmp[1])
			return (clean_strs(tmp, 0, 0), perror("file not found\n"), 1);
		if (!ft_strcmp(tmp[0], ">"))
			fd = open(tmp[1], O_CREAT | O_TRUNC | O_RDWR, 0666);
		if (!ft_strcmp(tmp[0], ">>"))
			fd = open(tmp[1], O_CREAT | O_APPEND | O_RDWR, 0666);
		if (!ft_strcmp(tmp[0], "<"))
			fd = open(tmp[1], O_RDONLY);
		if (!ft_strcmp(tmp[0], "<<"))
			fd = get_pipe(d, tmp[1]);
		if (fd < 0)
			return (clean_strs(tmp, 0, 0), perror("file not found\n"), 1);
		if ((!ft_strcmp(tmp[0], ">")) || (!ft_strcmp(tmp[0], ">>")))
			dup2(fd, 1);
		else
			dup2(fd, 0);
		close(fd);
		clean_strs(tmp, 0, 0);
	}
	return (0);
}
