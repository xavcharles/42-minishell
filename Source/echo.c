/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:25:22 by maderuel          #+#    #+#             */
/*   Updated: 2024/01/22 23:02:08 by xacharle         ###   ########.fr       */
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

int	tiret_n(char **tab)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		j = 1;
		if (tab[i][0] != '-')
			return (i + 1);
		while (tab[i][j] == 'n')
			j++;
		if (tab[i][j])
			return (i + 1);
		i++;
	}
	return (i + 1);
}

int	ft_echo(t_data *d, int cc)
{
	int		i;

	i = tiret_n(&d->cmd[cc].cmd_arg[1]);
	if (d->cmd[cc].cmd_arg[i])
	{
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
	else if (!d->cmd[cc].cmd_arg[1])
		write(1, "\n", 1);
	return ((g_ret = 0), 0);
}
