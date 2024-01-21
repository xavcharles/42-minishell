/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:25:06 by maderuel          #+#    #+#             */
/*   Updated: 2024/01/22 00:46:09 by xacharle         ###   ########.fr       */
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
			ft_exit(d, 126, -1);
		ft_exit(d, 127, -1);
	}
	return (ft_exit(d, 127, -1), EXIT_FAILURE);
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
				return (ft_exit(d, EXIT_FAILURE, -1), 1);
			}
		}
	}
	if (is_builtin(d, cc) > 0)
	{
		exec_builtin(d, cc);
	}
	else
		exec_2(d, cc);
	return (ft_exit(d, 127, -1), 1);
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
void	redirect_all(int i, int pipe[2], t_data *d)
{
	if (i != 0)
	{
		dup2(d->prev, 0);
		close(d->prev);
	}
	if (i != d->cmd_count -1)
		dup2(pipe[1], 1);
	close(pipe[0]);
	close(pipe[1]);
	if (d->cmd[0].all && redir_all(d, 0))
		ft_exit(d, 1, -1);
}

int	cmd_exec(t_data *d)
{
	int	i;
	t_pipe p;

	i = -1;
	if (d->cmd_count == 1 && is_builtin(d, 0))
	{
		// if (d->cmd[0].in && redir_in(d, 0))
			// return ((dup2(d->std_out, 1), dup2(d->std_in, 0)), 1);
		// if (d->cmd[0].out && redir_out(d, 0))
			// return ((dup2(d->std_out, 1), dup2(d->std_in, 0)), 1);
		if (d->cmd[0].all && redir_all(d, 0))
			return ((dup2(d->std_out, 1), dup2(d->std_in, 0)), 1);
		if (exec_builtin(d, 0))
			return ((dup2(d->std_out, 1), dup2(d->std_in, 0)), 1);
		return ((dup2(d->std_out, 1), dup2(d->std_in, 0)), 0);
	}
	d->prev = -1;
	while (++i < d->cmd_count && i < 1024)
	{
		if (pipe(p.end) == -1)
			return (1);
		d->allpids[i] = fork();
		if (!d->allpids[i])
		{
			close(d->std_in);
			close(d->std_out);
			redirect_all(i, p.end, d);
			if (!d->cmd->cmd)
				ft_exit(d, 0, -1);
			if (is_builtin(d, i)) 
			{
				exec_builtin(d, i);
				ft_exit(d, 0, -1);
			}
			exec_1(d, i);
			ft_exit(d, 127, -1);
		}
		else
		{
			close(p.end[1]);
			if (d->prev != -1)
				close(d->prev);
			d->prev = p.end[0];
		}
	}
	close(p.end[0]);
	i = -1;
	while (++i < d->cmd_count)
		waitpid(d->allpids[i], NULL, 0);
	return (0);
}
