/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:29:59 by xacharle          #+#    #+#             */
/*   Updated: 2024/01/20 17:30:01 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fill_in(char *str, char **in, int *i)
{
	int		start;
	char	*tmp;

	start = *i;
	while (str[*i] == '<')
		(*i)++;
	tmp = ft_substr(str, start, *i - start);
	if (!tmp)
		return (1);
	*in = gnl_strjoin(*in, tmp);
	if (!*in)
		return (free(tmp), 1);
	free(tmp);
	return (0);
}

int	fill_out(char *str, char **out, int *i)
{
	int		start;
	char	*tmp;

	start = *i;
	while (str[*i] == '>')
		(*i)++;
	tmp = ft_substr(str, start, *i - start);
	if (!tmp)
		return (1);
	*out = gnl_strjoin(*out, tmp);
	if (!*out)
		return (free(tmp), 1);
	free(tmp);
	return (0);
}

int	fill_justthesign(char *str, char **in, char **out, int *i)
{
	if (str[*i] == '<')
	{
		if (fill_in(str, in, i))
			return (1);
	}
	else
	{
		if (fill_out(str, out, i))
			return (1);
	}
	return (0);
}
