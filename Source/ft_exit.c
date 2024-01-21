/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maderuel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:30:39 by maderuel          #+#    #+#             */
/*   Updated: 2024/01/15 13:30:49 by maderuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(t_data *d, int n, int cc)
{
	int	i;
	int	j;
	char	first_char;

	i = 0;
	first_char = 0;
	if (cc >= 0 && d->cmd[cc].cmd_arg[1])
	{
		while (d->cmd[cc].cmd_arg[++i] && !first_char)
		{
			j = -1;
			if (i == 2)
			{
				printf("minishell: exit: too many arguments\n");
				return ;
			}
			while (d->cmd[cc].cmd_arg[i][++j])
			{
				if (!ft_isdigit(d->cmd[cc].cmd_arg[i][j]) && !first_char)
				{	
					first_char = d->cmd[cc].cmd_arg[i][j];
					printf("minishell: exit: %s: numeric argument required\n", d->cmd[cc].cmd_arg[i]);
					n = 2;
					break ;
				}
			}
			if (!first_char)
				n = ft_atoi(d->cmd[cc].cmd_arg[i]);
		}
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
