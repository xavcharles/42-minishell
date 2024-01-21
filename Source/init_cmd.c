/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:29:30 by xacharle          #+#    #+#             */
/*   Updated: 2024/01/22 00:46:06 by xacharle         ###   ########.fr       */
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
			return (free(*all), printf("Minishell: Failed Malloc in set_in_out\n"));
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

// int	loop_cmd(t_ccmd *ccmd, char **strs, char **in, char **out)
// {
// 	int		j;
// 	int		i;
// 	int		start;
// 	int		inquote;
// 	char	start_q;
// 	char	*tmp;
// 	char	*cmd_arg;

// 	j = 0;
// 	inquote = 0;
// 	cmd_arg = NULL;
// 	while (strs[j])
// 	{
// 		i = 0;
// 		while (strs[j][i])
// 		{
// 			if (!is_charset(strs[j][i], "<>"))
// 			{
// 				start = i;
// 				while (strs[j][i] && (!is_charset(strs[j][i], "<>") || inquote == 1))
// 				{
// 					if (is_charset(strs[j][i], "'\"") && inquote == 0)
// 					{
// 						inquote = 1;
// 						start_q = strs[j][i];
// 					}
// 					else if (inquote == 1 && strs[j][i] == start_q)
// 					{
// 						inquote = 0;
// 						start_q = 0;
// 					}
// 					i++;
// 				}
// 				tmp = ft_substr(strs[j], start, i - start);
// 				if (!tmp)
// 					return (1);
// 				if (*in && (*in)[ft_strlen(*in) - 1] == '<')
// 				{
// 					*in = join_w_tab(*in, tmp);
// 					if (!*in)
// 						return (free(tmp), 1);
// 				}
// 				else if (*out && (*out)[ft_strlen(*out) - 1] == '>')
// 				{
// 					*out = join_w_tab(*out, tmp);
// 					if (!*out)
// 						return (free(tmp), 1);
// 				}
// 				else
// 				{	
// 					cmd_arg = join_w_space(cmd_arg, tmp);
// 					if (!cmd_arg)
// 						return (free(tmp), 1);
// 				}
// 				free(tmp);
// 			}
// 			else
// 			{
// 				if (strs[j][i] == '<')
// 				{
// 					start = i;
// 					while(strs[j][i] == '<')
// 						i++;
// 					tmp = ft_substr(strs[j], start, i - start);
// 					if (!tmp)
// 						return (1);
// 					*in = gnl_strjoin(*in, tmp);
// 					if (!*in)
// 						return (free(tmp), 1);
// 					free(tmp);
// 					if (!strs[j][i])
// 						break ;
// 				}
// 				else
// 				{
// 					start = i;
// 					while(strs[j][i] == '>')
// 						i++;
// 					tmp = ft_substr(strs[j], start, i - start);
// 					if (!tmp)
// 						return (1);
// 					*out = gnl_strjoin(*out, tmp);
// 					if (!*out)
// 						return (free(tmp), 1);
// 					free(tmp);
// 					if (!strs[j][i])
// 						break ;
// 				}
// 			}
// 		}
// 		j++;
// 	}
// 	if (cmd_arg)
// 	{
// 		ccmd->cmd_arg = ms_split(cmd_arg, " ");
// 		if (!ccmd->cmd_arg)
// 			return (free(cmd_arg), 1);
// 		free(cmd_arg);
// 		ccmd->cmd = ft_strdup(ccmd->cmd_arg[0]);
// 		if (!ccmd->cmd)
// 			return (1);
// 	}
// 	return (0);
// }
