/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:29:59 by xacharle          #+#    #+#             */
/*   Updated: 2024/01/22 03:56:17 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fill_all(char *str, char **all, int *i)
{
	int		start;
	char	*tmp;

	start = *i;
	while (str[*i] == '>')
		(*i)++;
	while (str[*i] == '<')
		(*i)++;
	tmp = ft_substr(str, start, *i - start);
	if (!tmp)
		return (1);
	*all = gnl_strjoin(*all, tmp);
	if (!*all)
		return (free(tmp), 1);
	free(tmp);
	return (0);
}

int	fill_justthesign(char *str, char **all, int *i)
{
	return (fill_all(str, all, i));
}
