/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maderuel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:25:06 by maderuel          #+#    #+#             */
/*   Updated: 2024/01/15 16:27:12 by maderuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_2(t_data *d, int i, int cc)
{
	char	*tmp;

	tmp = ft_strjoin(d->paths[i], "/");
	tmp = gnl_strjoin(tmp, d->cmd[cc].cmd);
	if (!access(tmp, F_OK | X_OK))
	{
		if (execve(tmp, d->cmd[cc].cmd_arg, d->env) == -1)
		{
			free(tmp);
			perror(d->cmd[cc].cmd);
			exit(EXIT_FAILURE);
		}
	}
	free(tmp);
	return (1);
}

int	exec_1(t_data *d, int cc)
{
	int		i;

	i = 0;
	while (d->paths[i])
	{
		if (!ft_strncmp(d->cmd[cc].cmd, "./minishell",
				ft_strlen(d->cmd[cc].cmd)))
		{
			if (!access(d->cmd[cc].cmd, F_OK | X_OK))
			{
				if (execve(d->cmd[cc].cmd, d->cmd[cc].cmd_arg, d->env) == -1)
				{
					perror(d->cmd[cc].cmd);
					return (ft_exit(d, EXIT_FAILURE), 1);
				}
			}
		}
		else
			exec_2(d, i, cc);
		i++;
	}
	if (execve(d->cmd[cc].cmd, d->cmd[cc].cmd_arg, d->env) == -1)
		perror(d->cmd[cc].cmd);
	return (ft_exit(d, EXIT_FAILURE), 1);
}

int	exec_pipes(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->cmd_count - 1)
	{
		if (d->cmd[i].in)
			redir_in(&d->cmd[i]);
		ft_pipe(d, i);
		i++;
	}
	if (d->cmd[i].out)
		redir_out(&d->cmd[i]);
	if (!is_builtin1(d, i) && !is_builtin2(d, i))
		if (exec_1(d, i))
			return (printf("cmd error\n"), 1);
	exit(0);
}

int	simple_exec(t_data *d)
{
	if (d->cmd->in)
		redir_in(d->cmd);
	if (d->cmd->out)
		redir_out(d->cmd);
	if (!is_builtin1(d, 0) && !is_builtin2(d, 0))
		if (exec_1(d, 0))
			return (printf("cmd error\n"), 1);
	exit(0);
}

int	cmd_exec(t_data *d)
{
	int		status;
	t_pipe	p;

	p.pid1 = fork();
	if (p.pid1 == 0)
	{
		ic_sigs(2);
		if (d->cmd_count > 1)
			exec_pipes(d);
		else
			simple_exec(d);
	}
	else
	{
		signal(SIGQUIT, SIG_IGN);
		waitpid(p.pid1, &status, 0);
		if (is_builtin2(d, d->cmd_count - 1))
			return (1);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
			printf("Quit (Core Dumped)\n");
		g_ret = WEXITSTATUS(status);
	}
	return (0);
}
