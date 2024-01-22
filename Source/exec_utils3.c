/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maderuel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:29:42 by maderuel          #+#    #+#             */
/*   Updated: 2024/01/22 14:00:00 by maderuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	print(void)
{
	char	buf[50];
	int		ret;

	ret = 1;
	while (ret)
	{
		ret = read(0, buf, sizeof(buf));
		buf[ret] = '\0';
		write(1, buf, ret);
	}
}

void	reset_std(t_data *d, int i)
{
	dup2(d->std_out, 1);
	if (!d->cmd[i].next_op)
		dup2(d->std_in, 0);
}

char	*cmd_with_path(t_data *d, int cc)
{
	char	*tmp;
	char	**path;
	int		i;

	i = -1;
	tmp = NULL;
	path = pathman(d);
	while (path[++i])
	{
		if (ft_strlen(d->cmd[cc].cmd) == 0)
			tmp = d->cmd[cc].cmd;
		else
		{
			tmp = ft_strjoin(path[i], "/");
			tmp = gnl_strjoin(tmp, d->cmd[cc].cmd);
		}
		if (!access(tmp, F_OK | X_OK))
			return (clean_strs(path, 0, 0), tmp);
		if (ft_strlen(tmp) != 0)
			free(tmp);
	}
	clean_strs(path, 0, 0);
	return (d->cmd[cc].cmd);
}
