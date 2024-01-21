/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maderuel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:25:22 by maderuel          #+#    #+#             */
/*   Updated: 2024/01/17 14:48:37 by maderuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	eqote(t_data *d, int i, int cc)
{
	char	*str;

	if (d->cmd[cc].cmd_arg[i][0] == '"')
	{
		str = ft_strtrim(d->cmd[cc].cmd_arg[i], "\"");
		if (!str)
			return (exit(1), 1);
		ft_putstr_fd(str, 1);
		free(str);
	}
	else if (d->cmd[cc].cmd_arg[i][0] == '\'')
	{
		str = ft_strtrim(d->cmd[cc].cmd_arg[i], "'");
		if (!str)
			return (1);
		ft_putstr_fd(str, 1);
		free(str);
	}
	return (0);
}

int	ft_echo(t_data *d, int cc)
{
	int		i;

	i = 1;
	if (d->cmd[cc].cmd_arg[1])
	{
		if (!ft_strncmp(d->cmd[cc].cmd_arg[1], "-n", 2))
			i = 2;
		if (ft_strlen(d->cmd[cc].cmd) == 0)
			return (ft_exit(d, 127, -1), 1);
		while (d->cmd[cc].cmd_arg[i])
		{
			if (d->cmd[cc].cmd_arg[i][0] == '\''
				|| d->cmd[cc].cmd_arg[i][0] == '"')
				eqote(d, i, cc);
			else
				ft_putstr_fd(d->cmd[cc].cmd_arg[i], 1);
			i++;
			if (d->cmd[cc].cmd_arg[i])
				write(1, " ", 1);
		}
		if (ft_strncmp(d->cmd[cc].cmd_arg[1], "-n", 2))
			write(1, "\n", 1);
	}
	return (ft_exit(d, 0, -1), 0);
}
