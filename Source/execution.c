#include "../minishell.h"

int	exec_1(t_data *d, int cc)
{
	int		i;
	char 	*tmp;
	char	*cwp;

	i = 0;
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
	pid_t	pid;

	i = 0;
	pid = fork();
	if (pid == 0)
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
