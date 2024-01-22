/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:29:30 by xacharle          #+#    #+#             */
/*   Updated: 2024/01/22 03:51:49 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_clean(char **strs, char *all)
{
	if (strs)
		clean_strs(strs, 0, 0);
	if (all)
		free(all);
}

int	set_in_out(t_ccmd *ccmd, char **all)
{
	if (*all)
	{
		ccmd->all = ms_split(*all, "\t");
		if (!ccmd->all)
			return (free(*all),
				printf("Minishell: Failed Malloc in set_in_out\n"));
		free(*all);
	}
	return (0);
}

int	loop_cmd(t_ccmd *ccmd, char **strs, char **all)
{
	int		j;
	char	*cmd_arg;

	j = -1;
	cmd_arg = NULL;
	while (strs[++j])
	{
		if (loop_2(strs[j], &cmd_arg, all))
		{
			if (cmd_arg)
				free(cmd_arg);
			return (1);
		}
	}
	if (cmd_arg)
	{
		ccmd->cmd_arg = ms_split(cmd_arg, " ");
		if (!ccmd->cmd_arg)
			return (free(cmd_arg), 1);
		free(cmd_arg);
		ccmd->cmd = ft_strdup(ccmd->cmd_arg[0]);
		if (!ccmd->cmd)
			return (1);
	}
	return (0);
}

int	init_ccmd(t_data *d, t_ccmd *ccmd)
{
	int		i;
	char	**strs;
	char	*all;

	init_zero(d);
	i = -1;
	while (d->cmds[++i])
	{
		if (input_check(d))
			return (printf("Minishell: Incorrect synthax\n"));
		strs = ms_split(d->cmds[i], "\t ");
		if (!strs)
			return (printf("Minishell: Failed Malloc in init_ccmd\n"));
		all = NULL;
		if (loop_cmd(ccmd + i, strs, &all))
			return (init_clean(strs, all), 1);
		if (set_in_out(ccmd + i, &all))
			return (init_clean(strs, all), 1);
		clean_strs(strs, 0, 0);
	}
	return (0);
}
