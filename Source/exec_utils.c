/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maderuel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:51:52 by maderuel          #+#    #+#             */
/*   Updated: 2024/01/15 16:42:52 by maderuel         ###   ########.fr       */
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

int	is_builtin2(t_data *d, int cc)
{
	char	*cmd;

	cmd = d->cmd[cc].cmd;
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
	{
		if (par_cd(d, cc))
			return (1);
	}
	else if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
	{
		if (par_export(d, cc))
			return (1);
	}
	else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
	{
		if (par_unset(d, cc))
			return (1);
	}
	return (0);
}

int	is_builtin(t_data *d, int cc)
{
	char	*cmd;

	cmd = d->cmd[cc].cmd;
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
		return (print_env(d), 1);
	else if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
		return (ft_export(d, cc), 1);
	else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
		return (ft_unset(d, cc), 1);
	else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
		return (pwd_builtin(d, cc), 1);
	else if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
		return (cd_builtin(d, cc), 1);
	else if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
		return (ft_echo(d, 0), 1);
	return (0);
}
