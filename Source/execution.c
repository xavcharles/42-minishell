/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:25:06 by maderuel          #+#    #+#             */
/*   Updated: 2024/01/22 17:34:44 by maderuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_2(t_data *d, int cc)
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
}

int	cmd_exec_2(t_data *d, t_pipe *p, int i)
{
	close(d->std_in);
	close(d->std_out);
	redirect_all(i, p->end, d);
	if (!d->cmd->cmd)
		ft_exit(d, 0, -1);
	if (is_builtin(d, i))
	{
		if (exec_builtin(d, i))
			ft_exit(d, 127, -1);
		ft_exit(d, 0, -1);
	}
	exec_2(d, i);
	return (ft_exit(d, 127, -1), 0);
}

int	cmd_exec_1(t_data *d, t_pipe *p, int i)
{
	if (pipe(p->end) == -1)
		return (1);
	d->allpids[i] = fork();
	if (!d->allpids[i])
		cmd_exec_2(d, p, i);
	else
	{
		close(p->end[1]);
		if (d->prev != -1)
			close(d->prev);
		d->prev = p->end[0];
	}
	return (1);
}

int	cmd_exec_sb(t_data *d)
{
	if (d->cmd[0].all && redir_all(d, 0))
		return ((dup2(d->std_out, 1), dup2(d->std_in, 0)), 1);
	if (exec_builtin(d, 0))
		return ((dup2(d->std_out, 1), dup2(d->std_in, 0)), 1);
	return ((dup2(d->std_out, 1), dup2(d->std_in, 0)), 0);
}

int	cmd_exec(t_data *d)
{
	int		i;
	int		status;
	t_pipe	p;

	i = -1;
	if (d->cmd_count == 1 && is_builtin(d, 0))
		return (cmd_exec_sb(d));
	d->prev = -1;
	while (++i < d->cmd_count && i < 1024)
		cmd_exec_1(d, &p, i);
	close(p.end[0]);
	i = -1;
	while (++i < d->cmd_count)
	{
		waitpid(d->allpids[i], &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
			ft_dprintf(2, "Quit (Core Dumped)\n");
		g_ret = WEXITSTATUS(status);
	}
	return (0);
}
