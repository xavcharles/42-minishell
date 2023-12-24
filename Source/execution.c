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
			perror("Minishell");
			free(cwp);
			exit (1);
		}
	}
	return (0);
}

/*
int	multiexec(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->cmd_count)
	{
		if (d->cmd->in)
			redir_in(d);
		if (d->cmd->out)
			redir_out(d);
		ft_pipe(d, i + (i > 0));
		i++;
	}
	exec_1(d, i);
	return (0);
}
*/

int	cmd_exec(t_data *d)
{
	int	i;
	t_pipe p;

	i = 0;
	p.pid1 = fork();
	d->p = &p;
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
	wait(NULL);
	return (0);
}
