/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:27:38 by xacharle          #+#    #+#             */
/*   Updated: 2024/01/22 17:23:58 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*join_w_space(char *s1, char *s2)
{
	size_t	size;
	char	*str;

	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	str[0] = 0;
	if (s1)
	{
		ft_strlcat(str, s1, size + 1);
		str[ft_strlen(s1) + 1] = 0;
		str[ft_strlen(s1)] = ' ';
	}
	if (s2)
		ft_strlcat(str, s2, size + 1);
	if (s1)
		free(s1);
	return (str);
}

char	*join_w_tab(char *s1, char *s2)
{
	size_t	size;
	char	*str;

	size = ft_strlen(s1) + ft_strlen(s2) + 2;
	str = malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	str[0] = 0;
	if (s1)
	{
		ft_strlcat(str, s1, size + 1);
		str[ft_strlen(s1) + 1] = 0;
		str[ft_strlen(s1)] = ' ';
	}
	if (s2)
		ft_strlcat(str, s2, size + 1);
	str[size] = 0;
	str[size - 1] = '\t';
	if (s1)
		free(s1);
	return (str);
}

void	init_zero(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->cmd_count)
	{
		d->cmd[i].cmd = NULL;
		d->cmd[i].cmd_arg = NULL;
		d->cmd[i].all = NULL;
		i++;
	}
}

void	data_zero(t_data *d)
{
	d->cmd = NULL;
	d->cmds = NULL;
	d->seps = NULL;
	d->input = NULL;
	d->cmd_count = 0;
	d->sep_count = 0;
	d->prev = 0;
	d->hd = NULL;
	d->nb_heredoc = 0;
}
