/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maderuel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:25:06 by maderuel          #+#    #+#             */
/*   Updated: 2024/01/18 18:03:35 by maderuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_2(t_data *d, int cc)
{
	char	*tmp;
	int		i;

	i = -1;
	while (d->paths[++i])
	{
		tmp = ft_strjoin(d->paths[i], "/");
		tmp = gnl_strjoin(tmp, d->cmd[cc].cmd);
		if (!access(tmp, F_OK | X_OK))
		{
			if (execve(tmp, d->cmd[cc].cmd_arg, d->env) == -1)
			{
				free(tmp);
				if (errno == 13)
					exit(126);
				exit(127);
			}
		}
		free(tmp);
	}
	if (!access(d->cmd[cc].cmd, F_OK | X_OK))
		if (execve(d->cmd[cc].cmd, d->cmd[cc].cmd_arg, d->env) == -1)
			printf("Minishell : %s %s\n", d->cmd[cc].cmd, strerror(errno));
	return (ft_exit(d, 127), EXIT_FAILURE);
}

int	exec_1(t_data *d, int cc)
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
	else if (is_builtin(d, cc) == 1)
		exec_builtin(d, cc);
	else
		exec_2(d, cc);
	return (ft_exit(d, 2), 1);
}

int	simple_exec(t_data *d, int cc)
{
	if (d->cmd->in)
		redir_in(d, d->cmd + cc);
	if (d->cmd->out)
		redir_out(d, d->cmd + cc);
	if (d->cmd->cmd == NULL)
		exit(2);
	if (is_builtin(d, 0) == 1)
		exec_builtin(d, cc);
	else if (is_builtin(d, cc) == 2)
		ft_exit(d, 0);
	else if (exec_1(d, cc))
		return (printf("cmd error\n"), 1);
	return (ft_exit(d, 0), 0);
}

void	print(void)
{
	char	buf[50];
	int		ret;

	ret = 1;
	while (ret)
	{
		ret = read(0, buf, sizeof(buf));
		buf[ret] = '\0';
		write(1, buf, ret);
	}
}

int	exec_pipes(t_data *d)
{
	int	i;	

	i = -1;
	while (++i < d->cmd_count - 1)
	{

		if (d->cmd[i].in)
			redir_in(d, &d->cmd[i]);
		if (d->cmd[i].out)
			redir_out(d, &d->cmd[i]);
		ft_pipe(d, i);
		if (!isatty(0) && !isatty(1))
			print();
		dup2(d->std_out, 1);
	}
	simple_exec(d, i);
	dup2(d->std_in, 0);
	print();
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
			simple_exec(d, 0);
		while (wait(NULL) > 0)
			;
	}
	else
	{
		signal(SIGQUIT, SIG_IGN);
		waitpid(p.pid1, &status, 0);
		if (is_builtin(d, d->cmd_count - 1) == 2)
			exec_builtin(d, d->cmd_count - 1);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
			printf("Quit (Core Dumped)\n");
		g_ret = WEXITSTATUS(status);
	}
	return (0);
}
