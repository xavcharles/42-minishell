/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maderuel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:25:06 by maderuel          #+#    #+#             */
/*   Updated: 2024/01/21 17:29:04 by maderuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*cmd_with_path(t_data *d, int cc)
{
	char	*tmp;
	char	**path;
	int		i;

	i = -1;
	tmp = NULL;
	path = pathman(d);
	while (path[++i])
	{
		if (ft_strlen(d->cmd[cc].cmd) == 0)
			tmp = d->cmd[cc].cmd;
		else
		{
			tmp = ft_strjoin(path[i], "/");
			tmp = gnl_strjoin(tmp, d->cmd[cc].cmd);
		}
		if (!access(tmp, F_OK | X_OK))
			return (clean_strs(path, 0, 0), tmp);
		if (ft_strlen(tmp) != 0)
			free(tmp);
	}
	clean_strs(path, 0, 0);
	return (d->cmd[cc].cmd);
}

int	exec_2(t_data *d, int cc)
{
	char	*cmd;

	cmd = cmd_with_path(d, cc);
	if (execve(cmd, d->cmd[cc].cmd_arg, d->env) == -1)
	{
		if (cmd != d->cmd[cc].cmd)
			free(cmd);
		perror(d->cmd[cc].cmd);
		if (errno == 13)
			ft_exit(d, 126);
		ft_exit(d, 127);
	}
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
	if (is_builtin(d, cc) == 1)
	{
		dprintf(2, "cmd = %s\n", d->cmd[cc].cmd);
		exec_builtin(d, cc);
	}
	else
		exec_2(d, cc);
	return (ft_exit(d, 127), 1);
}

int	simple_exec(t_data *d, int cc)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		close(d->std_in);
		close(d->std_out);
		exec_1(d, cc);
	}
	else
	{
		signal(SIGQUIT, SIG_IGN);
		waitpid(pid, &status, 0);
		if (is_builtin(d, d->cmd_count - 1) == 2)
			exec_builtin(d, d->cmd_count - 1);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
			printf("Quit (Core Dumped)\n");
		g_ret = WEXITSTATUS(status);
	}
	return (0);
}


int	cmd_exec(t_data *d)
{
	int	i;

	i = -1;
	while (++i < d->cmd_count)
	{
		if (d->cmd->cmd == NULL)
			return (2);
		if (d->cmd[i].in)
			redir_in(d, i);
		if (d->cmd[i].out)
			redir_out(d, i);
		if (is_builtin(d, i) == 2)
			exec_builtin(d, i);
		if (d->cmd[i].next_op)
			ft_pipe(d, i);
		else if (is_builtin(d, i) != 2)
			simple_exec(d, i);
		if (!isatty(0) && !isatty(1))
			print();
		dup2(d->std_out, 1);
		if (!d->cmd[i].next_op)
			dup2(d->std_in, 0);
	}
	return (0);
}
