#include "../minishell.h"

int	is_builtin(t_data *d, int cc)
{
	char	*cmd;

	cmd = d->cmd[cc].cmd;
	if (!cmd)
		return (1);
	if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
		return (print_env(d), 1);
	else if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
		return (ft_export(d, cc), 1);
	else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
		return (ft_unset(d, cc), 1);
	else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
		return (pwd_builtin(d, cc), 1);
	else if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
		return (cd_builtin(d, cc), 1);
	else if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
		return (ft_echo(d, cc), 1);
	else if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)))
		return (ft_exit(d, 0), 1);
	return (0);
}

int	exec_1(t_data *d, int cc)
{
	int	i;
	char *tmp;

	i = 0;
	while (d->paths[i])
	{
		if (!ft_strncmp(d->cmd[cc].cmd, "./minishell", ft_strlen(d->cmd[cc].cmd)))
		{
			if (!access(d->cmd[cc].cmd, F_OK | X_OK))
			{
				if (execve(d->cmd[cc].cmd, d->cmd[cc].cmd_arg, d->env) == -1)
				{
					perror(d->cmd[cc].cmd);
					return (ft_exit(d, 1), 1);
				}
			}
		}
		else
		{
			tmp = ft_strjoin(d->paths[i], "/");
			tmp = gnl_strjoin(tmp, d->cmd[cc].cmd);
			if (!access(tmp, F_OK | X_OK))
			{
				if (execve(tmp, d->cmd[cc].cmd_arg, d->env) == -1)
				{
					free(tmp);
					perror(d->cmd[cc].cmd);
					exit(1);
				}
			}
			free(tmp);
		}
		i++;
	}
	printf("cest la\n");
	perror(d->cmd[cc].cmd);
	return (ft_exit(d, 1), 1);
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

int	is_builtin1(t_data *d, int cc)
{
	char	*cmd;

	cmd = d->cmd[cc].cmd;
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
		return (1);
	else if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
		return (1);
	else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
		return (1);
	else if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)))
		return (ft_exit(d, 0), 1);
	return (0);
}

int	is_builtin2(t_data *d, int cc)
{
	char	*cmd;

	cmd = d->cmd[cc].cmd;
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
	{
		if (par_cd(d, cc))
			return (1);
	}
	else if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
	{
		if (par_export(d, cc))
			return (1);
	}
	else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
	{
		if (par_unset(d, cc))
			return (1);
	}
	return (0);
}

int	cmd_exec(t_data *d)
{
	int	i;
	int status;
	t_pipe p;

	i = 0;
	printf("cmd count = %d\n", d->cmd_count);
	p.pid1 = fork();
	if (p.pid1 == 0)
	{
		ic_sigs(2);
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
			if (!is_builtin(d, i))
				exec_1(d, i);
		}
		else
		{
			if (d->cmd->in)
			{
				if(redir_in(d->cmd))
					return (1);
			}
			if (d->cmd->out)
				redir_out(d->cmd);
			if (!is_builtin(d, 0))
				exec_1(d, 0);
		}
	}
	else
	{
		// wait(NULL);
		printf("parent process, i = ? %d\n", i);
		signal(SIGQUIT, SIG_IGN);
		waitpid(p.pid1, &status, 0);
		if (is_builtin2(d, d->cmd_count - 1))
			return (1);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
		{
			printf("Quit (Core Dumped)\n");
		}
	}
	return (0);
}
