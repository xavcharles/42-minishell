/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:30:39 by maderuel          #+#    #+#             */
/*   Updated: 2024/01/22 12:53:53 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_synthax(t_data *d, int cc, int *n, char first_char)
{
	int	i;
	int	j;

	i = 0;
	while (d->cmd[cc].cmd_arg[++i] && !first_char)
	{
		j = -1;
		if (i == 2)
			return (ft_dprintf(2, "minishell: exit: too many arguments\n"), 1);
		while (d->cmd[cc].cmd_arg[i][++j])
		{
			if (!ft_isdigit(d->cmd[cc].cmd_arg[i][j]) && !first_char)
			{	
				first_char = d->cmd[cc].cmd_arg[i][j];
				ft_dprintf(2, "minishell: exit: %s: numeric argument required\n",
					d->cmd[cc].cmd_arg[i]);
				*n = 2;
				break ;
			}
		}
		if (!first_char)
			*n = ft_atoi(d->cmd[cc].cmd_arg[i]);
	}
	return (0);
}
void	ft_exit(t_data *d, int n, int cc)
{
	char	first_char;

	first_char = 0;
	if (cc >= 0 && d->cmd[cc].cmd_arg[1])
	{
		if (exit_synthax(d, cc, &n, first_char))
			return ;
	}
	if (d)
	{
		clean_data(d);
		if (d->paths)
			clean_strs(d->paths, 0, 0);
		if (d->env)
			clean_strs(d->env, 0, 0);
		if (d->input)
			free(d->input);
		rl_clear_history();
		free(d);
	}
	exit(n);
}
