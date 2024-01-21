/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maderuel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:28:49 by maderuel          #+#    #+#             */
/*   Updated: 2024/01/21 18:21:40 by maderuel         ###   ########.fr       */
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
		if (ft_strlen(tmp[0]) == 2)
			p.f2 = open(tmp[1], O_CREAT | O_RDWR | O_APPEND, 0777);
		else
			p.f2 = open(tmp[1], O_CREAT | O_RDWR | O_TRUNC, 0777);
		clean_strs(tmp, 0, 0);
	}
	if (p.f2 < 0)
	{
		printf("file not found\n");
		return (0);
	}
	dup2(p.f2, 1);
	close(p.f2);
	return (0);
}

void	get_doc(t_data *d, char *end, int *p_fd, char **strs)
{
	char	*str;

	close(p_fd[0]);
	close(d->std_in);
	close(d->std_out);
	while (1)
	{		
		ic_sigs(3);
		str = readline("here_doc $>");
		if (g_ret == 130 || ft_strncmp(str, end, ft_strlen(end)) == 0
			|| str == NULL)
		{
			free(str);
			close(p_fd[1]);
			clean_strs(strs, 0, 0);
			return (ft_exit(d, 0));
		}
		ft_putstr_fd(str, p_fd[1]);
		ft_putchar_fd('\n', p_fd[1]);
		free(str);
	}
	close(p_fd[1]);
	return ;
}

void	last_hd(pid_t pid, int p_fd[2], int status)
{
	close(p_fd[1]);
	dup2(p_fd[0], 0);
	close(p_fd[0]);
	waitpid(pid, &status, 0);
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
		get_doc(d, strs[1], p_fd, strs);
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

int	redir_in(t_data *d, int cc)
{
	t_pipe	p;
	char	**tmp;
	int		i;

	i = -1;
	while (d->cmd[cc].in[++i])
	{
		tmp = ft_split(d->cmd[cc].in[i], ' ');
		if (ft_strlen(tmp[0]) == 1)
		{
			p.f1 = open(tmp[1], O_RDONLY);
			if (p.f1 == -1)
			{
				clean_strs(tmp, 0, 0);
				perror("file not found\n");
				return (0);
			}
			dup2(p.f1, 0);
			close(p.f1);
		}
		else
			here_doc(d, tmp, cc, i);
		clean_strs(tmp, 0, 0);
	}
	return (0);
}
