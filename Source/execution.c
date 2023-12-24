#include "../minishell.h"

char	*cmd_with_path(t_data *d, int cc)
{
	int	i;
	char	*testcmd;
	char	*testpath;

	i = -1;
	while(d->paths[++i])
	{
		testpath = ft_strjoin(d->paths[i], "/");
		testcmd = ft_strjoin(testpath, d->cmd[cc].cmd);
		free(testpath);
		if (access(testcmd, F_OK | X_OK) == 0)
			return (testcmd);
		free(testcmd);
	}
	testcmd = ft_strdup(d->cmd[cc].cmd);
	return (testcmd);
}

int	is_builtin(t_data *d, int cc)
{
	if (!ft_strncmp(d->cmd[cc].cmd, "env", 3))
		return (print_env(d), 1);
	else if (!ft_strncmp(d->cmd[cc].cmd, "export", 6))
		return (ft_export(d), 1);
	else if (!ft_strncmp(d->cmd[cc].cmd, "unset", 5))
		return (ft_unset(d), 1);
	else if (!ft_strncmp(d->cmd[cc].cmd, "pwd", 3))
		return (printf("pwd\n"), 1);
	else if (!ft_strncmp(d->cmd[cc].cmd, "cd", 2))
		return (printf("cd\n"), 1);
	else if (!ft_strncmp(d->cmd[cc].cmd, "echo", 4))
		return (printf("echo\n"), 1);
	return (0);
}

int	exec_1(t_data *d, int cc)
{
	char	*cwp;

	if (is_builtin(d, cc))
		exit(0);
	else
	{
		cwp = cmd_with_path(d, cc);
		if (execve(cwp, d->cmd[cc].cmd_arg, d->env) == -1)
		{
<<<<<<< HEAD
			perror("Minishell");
=======
			tmp = ft_strjoin(d->paths[i], "/");
			cwp = ft_strjoin(tmp, d->cmd[cc].cmd);
			free(tmp);
			if (!access(cwp, X_OK))
			{
				if (execve(cwp, d->cmd[cc].cmd_arg, d->env) == -1)
				{
					perror("Minishell");
					free(cwp);
					exit (1);
				}
			}
>>>>>>> a89cff3 (exec a verif, built in a refaire)
			free(cwp);
			exit (1);
		}
	}
	perror(d->cmd[cc].cmd);
	exit (0);
}

<<<<<<< HEAD
/*
int	multiexec(t_data *d)
=======
int	tab_len(char **tab)
>>>>>>> a89cff3 (exec a verif, built in a refaire)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return i;
}

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

int	cmd_exec(t_data *d)
{
	int	i;
	t_pipe p;

	i = 0;
	p.pid1 = fork();
	if (pipe(p.end))
		return (perror("pipe"), 1);
	d->p = &p;
	if (p.pid1 == 0)
	{
		close(p.end[0]);
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
	close(p.end[1]);
	wait(NULL);
	if (!ft_strncmp(d->cmd->cmd, "export", 6))
		d->env = env_read(p.end[0]);
	return (0);
}
