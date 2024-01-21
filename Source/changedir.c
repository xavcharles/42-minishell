/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changedir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maderuel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:24:21 by maderuel          #+#    #+#             */
/*   Updated: 2024/01/21 18:40:53 by maderuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*sub_dir(char *s)
{
	int		i;
	char	*rs;

	i = ft_strlen(s) - 2;
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
	return (rs);
}

int	update_pwd2(t_data *d, int cc, int i)
{
	char	**tmp;
	char	*s;

	tmp = ft_split(d->env[i], '=');
	free(tmp[1]);
	free(d->env[i]);
	s = ft_strjoin(tmp[0], "=");
	free(tmp[0]);
	d->env[i] = ft_strjoin(s, d->cmd[cc].cmd_arg[1]);
	free(tmp);
	free(s);
	return (0);
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
	else if (ft_strnstr(d->env[i],
			d->cmd[cc].cmd_arg[1], ft_strlen(d->env[i])) != 0)
		update_pwd2(d, cc, i);
	else
	{
		s = ft_strjoin(d->env[i], "/");
		free(d->env[i]);
		d->env[i] = ft_strjoin(s, d->cmd[cc].cmd_arg[1]);
	}
	free(s);
	return (1);
}

int	update_oldpwd(t_data *d)
{
	int		i;
	int		j;
	char	**s;

	i = -1;
	j = -1;
	while (d->env[++i])
		if (!ft_strncmp(d->env[i], "OLDPWD", 6))
			break ;
	while (d->env[++j])
		if (!ft_strncmp(d->env[j], "PWD", 3))
			break ;
	s = ft_split(d->env[j], '=');
	free(s[0]);
	s[0] = ft_strjoin("OLDPWD", "=");
	free(d->env[i]);
	d->env[i] = ft_strjoin(s[0], s[1]);
	free(s[0]);
	free(s[1]);
	free(s);
	return (0);
}

int	cd_builtin(t_data *d, int cc)
{
	char	*dir;

	dir = d->cmd[cc].cmd_arg[1];
	if (chdir(dir) == 0)
	{
		update_oldpwd(d);
		update_pwd(d, cc);
		return (EXIT_SUCCESS);
	}
	g_ret = 1;
	perror(dir);
	return (EXIT_FAILURE);
}
