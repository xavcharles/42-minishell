#include "../minishell.h"

int	built_in(t_data *d, int cc)
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
	int		i;
	char 	*tmp;
	char	*cwp;

	i = 0;
	if (built_in(d, cc))
		return (0);
	else
	{
		while (d->paths[i])
		{
			tmp = ft_strjoin(d->paths[i], "/");
			cwp = ft_strjoin(tmp, d->cmd[cc].cmd);
			free(tmp);
			if (!access(cwp, X_OK))
			{
				if (execve(cwp, d->cmd[cc].cmd_arg, d->env) == -1)
				{
					perror("Minishell");
					free(cwp);
					return (1);
				}
			}
			free(cwp);
			i++;
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
