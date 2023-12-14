#include "../minishell.h"

int	redir_out(t_data *d)
{
	t_pipe	p;
	int	i;
	char	**tmp;

	i = -1;
	while (d->cmd->out[++i])
	{
		tmp = ft_split(d->cmd->out[i], ' ');
		if (ft_strlen(tmp[0]) == 2)
			p.f2 = open(tmp[1], O_CREAT | O_RDWR | O_APPEND, 0777);
		else
			p.f2 = open(tmp[1], O_CREAT | O_RDWR | O_TRUNC, 0777);
		clean_strs(tmp, 0, 0);
	}
	if (p.f2 < 0)
	{
		printf("file not found\n");
		return (1);
	}
	dup2(p.f2, 1);
	close(p.f2);
	return (0);
}

int	get_doc(char *end, int *p_fd)
{
	char *str;

	close(p_fd[0]);
	while (1)
	{
		str = readline("here_doc $>");
		if (ft_strncmp(str, end, ft_strlen(end)) == 0)
		{
			free(str);
			return (0);
		}
		ft_putstr_fd(str, p_fd[1]);
		free(str);
	}
}

int	here_doc(char *end)
{
	int	p_fd[2];
	pid_t	pid;

	if (pipe(p_fd) < 0)
		return (1);
	pid = fork();
	if (pid < 0)
		return (2);
	if (pid == 0)
		get_doc(end, p_fd);
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		close(p_fd[0]);
		wait(NULL);
	}
	return (0);
}

int	redir_in(t_data *d)
{
	t_pipe	p;
	char	**tmp;
	int		i;

	i = -1;
	while (d->cmd->in[++i])
	{
		tmp = ft_split(d->cmd->in[i], ' ');
		if (ft_strlen(tmp[0]) == 1)
			p.f1 = open(tmp[1], O_RDONLY);
		else
			here_doc(tmp[1]);
		clean_strs(tmp, 0, 0);
	}
	if (p.f1 < 0)
	{
		printf("file not found\n");
		return (1);
	}
	dup2(p.f1, 0); 
	close(p.f1);
	return(0);
}
