/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changedir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maderuel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:24:21 by maderuel          #+#    #+#             */
/*   Updated: 2024/01/16 18:55:34 by maderuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char	*sub_dir(char *s)
{
	int	i;
	char	*rs;

	i = ft_strlen(s) - 1;
	while (s[i])
	{
		if (s[i] == '/')
			break ;
		i--;
	}
	rs = malloc(sizeof(char) * i + 1);
	if (rs == NULL)
		return (NULL);
	ft_strlcpy(rs, s, i + 1);
	free(s);
	return(rs);
}

int	update_pwd(t_data *d, int cc)
{
	int		i;
	char	*s;

	i = -1;
	s = NULL;
	while (d->env[++i])
		if (!ft_strncmp(d->env[i], "PWD", 3))
			break ;	
	if (!ft_strncmp(d->cmd[cc].cmd_arg[1], "..", 2))
		d->env[i] = sub_dir(d->env[i]);
	else
	{
		s = ft_strjoin(d->env[i], "/");
		free(d->env[i]);
		d->env[i] = ft_strjoin(s, d->cmd[cc].cmd_arg[1]);
	}
	free(s);
	return (1);
}

int	cd_builtin(t_data *d, int cc)
{
	char	*dir;

	dir = d->cmd[cc].cmd_arg[1];
	if (chdir(dir) == 0)
	{
		update_pwd(d, cc);
		return (EXIT_SUCCESS);
	}
	perror(dir);
	return (EXIT_FAILURE);
}
