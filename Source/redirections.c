/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:28:49 by maderuel          #+#    #+#             */
/*   Updated: 2024/01/21 23:40:25 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_out(t_data *d, int cc)
{
	t_pipe	p;
	int		i;
	char	**tmp;

	i = -1;
	while (d->cmd[cc].out[++i] != NULL)
	{
		tmp = ft_split(d->cmd[cc].out[i], ' ');
		if (!tmp[1])
			return (clean_strs(tmp, 0, 0), ft_putstr_fd("file not found\n", 2), 1);
		if (ft_strlen(tmp[0]) == 2)
			p.f2 = open(tmp[1], O_CREAT | O_RDWR | O_APPEND, 0666);
		else
			p.f2 = open(tmp[1], O_CREAT | O_RDWR | O_TRUNC, 0666);
		clean_strs(tmp, 0, 0);
		if (p.f2 < 0)
		{
			printf("file not found\n");
			return (1);
		}
		dup2(p.f2, 1);
		close(p.f2);
	}
	return (0);
}

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

void	get_doc(t_data *d, char *end, int *p_fd, char **strs)
{
	char	*str;

	close(p_fd[0]);
	// close(d->std_in);
	// close(d->std_out);
	while (1)
	{		
		ic_sigs(3);
		str = readline("here_doc $>");
		if (break_doc_loop(end, str))
			break ;
		ft_putstr_fd(str, p_fd[1]);
		ft_putchar_fd('\n', p_fd[1]);
		free(str);
	}
	close(p_fd[1]);
	clean_strs(strs, 0, 0);
	(void) d;
}

void	last_hd(pid_t pid, int p_fd[2], int status)
{
	close(p_fd[1]);
	waitpid(pid, &status, 0);
	dup2(p_fd[0], 0);
	close(p_fd[0]);
	g_ret = WEXITSTATUS(status);
}

int	here_doc(t_data *d, char **strs, int cc, int i)
{
	int		p_fd[2];
	int		status;
	pid_t	pid;

	status = 0;
	if (pipe(p_fd) < 0)
		return (1);
	pid = fork();
	if (pid < 0)
		return (2);
	if (pid == 0)
	{
		get_doc(d, strs[1], p_fd, strs);
		ft_exit(d, g_ret, -1);
	}
	if (d->cmd[cc].in[i + 1] != NULL)
	{
		close(p_fd[1]);
		waitpid(pid, &status, 0);
		close(p_fd[0]);
	}
	else
		last_hd(pid, p_fd, status);
	return (0);
}
int		get_pipe(t_data *d, char *delim)
{
	int j = 0;
	while (j < d->nb_heredoc)
	{
		if (!ft_strcmp(d->hd[j].delim, delim))
			return (d->hd[j].fd[0]);
		j++;
	}
	return (-1);
}

int	redir_in(t_data *d, int cc)
{
	t_pipe	p;
	char	**tmp;
	int		i;

	i = -1;
	if (!d->cmd[cc].in)
		return (1);
	while (d->cmd[cc].in[++i])
	{
		tmp = ft_split(d->cmd[cc].in[i], ' ');
		if (!tmp[1])
			return (clean_strs(tmp, 0, 0), perror("file not found\n"), 1);
		if (ft_strlen(tmp[0]) == 1) // <
		{
			p.f1 = open(tmp[1], O_RDONLY);
			if (p.f1 == -1)
			{
				clean_strs(tmp, 0, 0);
				perror("file not found\n");
				return (1);
			}
			dup2(p.f1, 0);
			close(p.f1);
		}
		else // <<
		{
			p.f1 = get_pipe(d, tmp[1]);
			dup2(p.f1, 0);
			// here_doc(d, tmp, cc, i);
		}
		clean_strs(tmp, 0, 0);
	}
	return (0);
}
