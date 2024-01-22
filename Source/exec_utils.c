/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:51:52 by maderuel          #+#    #+#             */
/*   Updated: 2024/01/22 19:15:22 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_env(t_data *d, int cc)
{
	int	i;

	i = -1;
	if (d->cmd[cc].cmd_arg[1])
		return (ft_dprintf(2, "no arg pleas\n"), 1);
	while (d->env[++i] != NULL)
	{
		if (ft_strchr(d->env[i], '='))
			printf("%s\n", d->env[i]);
	}
	return ((g_ret = 0), 0);
}

int	is_builtin(t_data *d, int cc)
{
	char	*cmd;

	cmd = d->cmd[cc].cmd;
	if (!cmd || ft_strlen(cmd) == 0)
		return (0);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "history"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	exec_builtin(t_data *d, int cc)
{
	char	*cmd;

	cmd = d->cmd[cc].cmd;
	if (!ft_strcmp(cmd, "cd"))
		return (cd_builtin(d, cc));
	else if (!ft_strcmp(cmd, "export"))
		return (par_export(d, cc));
	else if (!ft_strcmp(cmd, "unset"))
		return (par_unset(d, cc));
	else if (!ft_strcmp(cmd, "env"))
		return (print_env(d, cc));
	else if (!ft_strcmp(cmd, "pwd"))
		return (pwd_builtin(d, cc));
	else if (!ft_strcmp(cmd, "echo"))
		return (ft_echo(d, cc));
	else if (!ft_strcmp(cmd, "history"))
		return (print_history(d, cc));
	else if (!ft_strcmp(cmd, "exit"))
		return (ft_exit(d, 0, cc), 1);
	return (0);
}

char	**pathman(t_data *d)
{
	int		i;
	char	**ret;

	i = -1;
	while (d->env[++i])
		if (ft_strncmp(d->env[i], "PATH", 4) == 0)
			break ;
	if (!d->env[i])
		return (NULL);
	ret = ft_split(d->env[i] + 5, ':');
	return (ret);
}

int	abs_exec(t_data *d, int cc)
{	
	if (!access(d->cmd[cc].cmd, F_OK | X_OK))
	{
		if (execve(d->cmd[cc].cmd, d->cmd[cc].cmd_arg, d->env) == -1)
		{
			perror(d->cmd[cc].cmd);
			if (errno == 13)
				ft_exit(d, 126, -1);
			ft_exit(d, 127, -1);
		}
	}
	perror(d->cmd[cc].cmd);
	return (ft_exit(d, 127, -1), 0);
}
