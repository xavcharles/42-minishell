/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:30:39 by maderuel          #+#    #+#             */
/*   Updated: 2024/01/23 10:50:48 by maderuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_n(char *arg, unsigned int *n, char first_char)
{
	if (!first_char || (is_charset(first_char, "+-") && *n != 2))
		*n = ft_atoi(arg);
}

int	exit_synthax(t_data *d, int cc, unsigned int *n, char fc)
{
	int	i;
	int	j;

	i = 0;
	while (d->cmd[cc].cmd_arg[++i] && !fc)
	{
		j = -1;
		if (i == 2)
			return (ft_dprintf(2, "minishell: exit: too many arguments\n"), 1);
		while (d->cmd[cc].cmd_arg[i][++j])
		{
			if (!ft_isdigit(d->cmd[cc].cmd_arg[i][j]) && (is_charset(fc, "+-")))
			{	
				fc = d->cmd[cc].cmd_arg[i][j];
				if (is_charset(fc, "+-") && j == 0)
					continue ;
				ft_dprintf(2, "minishell: exit: %s: numeric argument required\n",
					d->cmd[cc].cmd_arg[i]);
				*n = 2;
				break ;
			}
		}
		change_n(d->cmd[cc].cmd_arg[i], n, fc);
	}
	return (0);
}

void	ft_exit_clean(t_data *d)
{
	clean_data(d);
	clean_strs(d->paths, d->env, 0);
	if (d->pwd)
		free(d->pwd);
	if (d->input)
		free(d->input);
	rl_clear_history();
	close(d->std_in);
	close(d->std_out);
	free(d);
}

void	ft_exit(t_data *d, unsigned int n, int cc)
{
	char	first_char;

	first_char = 0;
	if (cc >= 0 && d->cmd[cc].cmd_arg[1])
	{
		if (exit_synthax(d, cc, &n, first_char))
		{
			g_ret = 1;
			return ;
		}
	}
	if (d)
		ft_exit_clean(d);
	if (cc >= 0)
		printf("exit\n");
	exit(n);
}
