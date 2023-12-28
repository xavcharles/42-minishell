#include "../minishell.h"

int	is_builtin(t_data *d, int cc)
{
	if (!ft_strncmp(d->cmd[cc].cmd, "env", 3))
		return (print_env(d), 1);
	else if (!ft_strncmp(d->cmd[cc].cmd, "export", 6))
		return (ft_export(d), 1);
	else if (!ft_strncmp(d->cmd[cc].cmd, "unset", 5))
		return (ft_unset(d, cc), 1);
	else if (!ft_strncmp(d->cmd[cc].cmd, "pwd", 3))
		return (printf("pwd\n"), 1);
	else if (!ft_strncmp(d->cmd[cc].cmd, "cd", 2))
		return (printf("cd\n"), 1);
	else if (!ft_strncmp(d->cmd[cc].cmd, "echo", 4))
		return (ft_echo(d, 0), 1);
	return (0);
}

int	exec_1(t_data *d, int cc)
{
	int	i;
	char *tmp;

	i = 0;
	while (d->paths[i])
	{
		tmp = ft_strjoin(d->paths[i], "/");
		tmp = ft_strjoin(tmp, d->cmd[cc].cmd);
		if (!access(tmp, X_OK))
		{
			if (execve(tmp, d->cmd[cc].cmd_arg, d->env) == -1)
			{
				free(tmp);
				perror("Minishell");
				exit (1);
			}
		}
		free(tmp);
		i++;
	}
	perror(d->cmd[cc].cmd);
	exit (0);
}

/*
char	**env_read(int fd)
{
	int		i;
	char	buf[BUF_ENV]; 	
	char	**tmp;

	i = 0;
	tmp = NULL;
	while (1)
	{
		if (read(fd, buf, sizeof(buf)) == 0)
			break ;
		tmp = realloc(tmp, (i + 2) * sizeof(char *));
		tmp[i] = ft_strdup(buf);
		tmp[++i] = NULL;
	}
	close(fd);
	return (tmp);
}
*/

int	cmd_exec(t_data *d)
{
	int	i;
	t_pipe p;

	i = 0;
	if (is_builtin(d, 0))
		return (0);
	p.pid1 = fork();
	if (p.pid1 == 0)
	{
		if (d->cmd_count > 1)
		{
			while (i < d->cmd_count - 1)
			{
				if (d->cmd[i].in)
					redir_in(&d->cmd[i]);
				ft_pipe(d, i);
				i++;
			}
			if (d->cmd[i].out)
				redir_out(&d->cmd[i]);
			exec_1(d, i);
		}
		else
		{
			if (d->cmd->in)
				if(redir_in(d->cmd))
					return (1);
			if (d->cmd->out)
				redir_out(d->cmd);
			if (exec_1(d, 0))
				return (printf("cmd error\n"), 1);
		}
	}
	else
	{
		wait(NULL);
	}
	return (0);
}
