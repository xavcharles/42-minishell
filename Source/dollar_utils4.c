/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 20:00:07 by xacharle          #+#    #+#             */
/*   Updated: 2024/01/22 00:46:11 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	d_quotehd(char **tmp, char *arg, int *k)
{
	int		start;
	char	**strs;
	char	*str;

	start = *k;
	while (arg[++(*k)] != '"')
		;
	str = ft_substr(arg, start, *k - start);
	if (!str)
		return (1);
	strs = ft_split(str, '"');
	if (!strs)
		return (free(str), 1);
	free(str);
	str = minijoin(strs);
	if (!str)
		return (clean_strs(strs, 0, 0), 1);
	clean_strs(strs, 0, 0);
	*tmp = ft_substr(arg, 0, start);
	if (!(*tmp))
		return (free(str), 1);
	*tmp = gnl_strjoin(*tmp, str);
	if (!(*tmp))
		return (free(str), 1);
	return (free(str), 0);
}

int	do_dquotehd(t_data *d, char **rep, int *k)
{
	char	*tmp;
	char	*arg;

	arg = *rep;
	if (d_quotehd(&tmp, arg, k))
		return (1);
	*rep = gnl_strjoin(tmp, arg + *k + 1);
	if (!*rep)
		return (free(arg), 1);
	free(arg);
	*k -= 2;
	(void) d;
	return (0);
}

int	dollar_loophd(t_data *d, t_ccmd *ccmd, char **rep, int *k)
{
	char	*arg;

	arg = *rep;
	if (arg[*k] == '\'')
	{
		if (do_squote(d, ccmd, rep, k))
			return (1);
	}
	else if (arg[*k] == '"')
	{
		if (do_dquotehd(d, rep, k))
			return (1);
	}
	return (0);
}

int	dollar_in(t_data *d, t_ccmd *cmd)
{
	int	i;
	int	j;

	i = -1;
	while (cmd->all[++i])
	{
		j = -1;
		while (cmd->all[i][++j])
		{
			if (!ft_strncmp(cmd->all[i], "<<", 2))
			{
				if (dollar_loophd(d, cmd, cmd->all + i, &j))
					return (1);
			}
			else
			{
				if (dollar_loop(d, cmd, cmd->all + i, &j))
					return (1);
			}
		}
	}
	return (0);
}

int	dollar_inout(t_data *d, t_ccmd *cmd)
{

	// if (cmd->all)
	// {
	// 	i = -1;
	// 	while (cmd->all[++i])
	// 	{
	// 		j = -1;
	// 		while (cmd->all[i][++j])
	// 		{
	// 			if (dollar_loop(d, cmd, cmd->all + i, &j))
	// 				return (1);
	// 		}
	// 	}
	// }
	if (cmd->all)
	{
		if (dollar_in(d, cmd))
			return (1);
	}
	return (0);
}
