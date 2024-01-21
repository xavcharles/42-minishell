/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:29:30 by xacharle          #+#    #+#             */
/*   Updated: 2024/01/21 17:42:11 by maderuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_clean(char **strs, char *in, char *out)
{
	if (strs)
		clean_strs(strs, 0, 0);
	if (in)
		free(in);
	if (out)
		free(out);
}

int	set_in_out(t_ccmd *ccmd, char **in, char **out)
{
	if (*in)
	{
		ccmd->in = ms_split(*in, "\t");
		if (!ccmd->in)
			return (printf("Minishell: Failed Malloc in set_in_out\n"));
		free(*in);
	}
	if (*out)
	{
		ccmd->out = ms_split(*out, "\t");
		if (!ccmd->out)
		{
			if (*in)
			{
				printf("Minishell: Failed Malloc in set_in_out\n");
				return (free(*in), 1);
			}
			return (printf("Minishell: Failed Malloc in set_in_out\n"));
		}
		free(*out);
	}
	return (0);
}

int	loop_cmd(t_ccmd *ccmd, char **strs, char **in, char **out)
{
	int		j;
	char	*cmd_arg;

	j = -1;
	cmd_arg = NULL;
	while (strs[++j])
	{
		if (loop_2(strs[j], &cmd_arg, in, out))
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
	char	*in;
	char	*out;
	char	**strs;

	init_zero(d);
	i = -1;
	while (d->cmds[++i])
	{
		if (input_check(d))
			return (printf("Minishell: Incorrect synthax\n"));
		strs = ms_split(d->cmds[i], "\t ");
		if (!strs)
			return (printf("Minishell: Failed Malloc in init_ccmd\n"));
		in = NULL;
		out = NULL;
		if (loop_cmd(ccmd + i, strs, &in, &out))
			return (init_clean(strs, in, out), 1);
		if (set_in_out(ccmd + i, &in, &out))
			return (init_clean(strs, in, out), 1);
		clean_strs(strs, 0, 0);
	}
	return (0);
}
