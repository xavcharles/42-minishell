/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maderuel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:51:52 by maderuel          #+#    #+#             */
/*   Updated: 2024/01/20 16:16:41 by maderuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	print_env(t_data *d)
{
	int	i;

	i = -1;
	while (d->env[++i] != NULL)
	{
		if (ft_strchr(d->env[i], '='))
			printf("%s\n", d->env[i]);
	}
	return (ft_exit(d, 0), 0);
}

int	is_builtin(t_data *d, int cc)
{
	char	*cmd;

	cmd = d->cmd[cc].cmd;
	if (!cmd || ft_strlen(cmd) == 0)
		return (0);
	if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
		return (2);
	else if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
		return (2);
	else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
		return (2);
	else if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
		return (1);
	else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
		return (1);
	else if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
		return (1);
	return (0);
}

int	exec_builtin(t_data *d, int cc)
{
	char	*cmd;

	cmd = d->cmd[cc].cmd;
	if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
		return (cd_builtin(d, cc));
	else if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
		return (par_export(d, cc));
	else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
		return (par_unset(d, cc));
	else if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
		return (print_env(d));
	else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
		return (pwd_builtin(d, cc));
	else if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
		return (ft_echo(d, cc));
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
	ret = ft_split(d->env[i], ':');
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
				ft_exit(d, 126);
			ft_exit(d, 127);
		}
	}
	perror(d->cmd[cc].cmd);
	return (ft_exit(d, 127), 0);
}
