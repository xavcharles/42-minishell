/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changedir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:24:21 by maderuel          #+#    #+#             */
/*   Updated: 2024/01/22 17:32:27 by maderuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	update_pwd(t_data *d)
{
	int		i;
	char	**tmp;

	i = -1;
	while (d->env[++i])
		if (!ft_strncmp(d->env[i], "PWD", 3))
			break ;
	tmp = ft_split(d->env[i], '=');
	free(d->env[i]);
	free(tmp[1]);
	tmp[1] = ft_strjoin(tmp[0], "=");
	d->env[i] = ft_strjoin(tmp[1], d->pwd);
	clean_strs(tmp, 0, 0);
	return (0);
}

int	update_oldpwd(t_data *d)
{
	int		i;
	char	**s;

	i = -1;
	while (d->env[++i])
		if (!ft_strncmp(d->env[i], "OLDPWD", 6))
			break ;
	s = ft_split(d->env[i], '=');
	free(d->env[i]);
	free(s[1]);
	s[1] = ft_strjoin(s[0], "=");
	d->env[i] = ft_strjoin(s[1], d->pwd);
	clean_strs(s, 0, 0);
	return (0);
}

int	cd_builtin(t_data *d, int cc)
{
	char	*dir;
	int		i;

	i = -1;
	dir = d->cmd[cc].cmd_arg[1];
	if (!dir)
	{
		while (d->env[++i])
			if (!ft_strncmp(d->env[i], "HOME", 4))
				break ;
		if (!d->env[i])
			return (ft_putstr_fd("HOME not set\n", 2), EXIT_FAILURE);
		return (chdir(d->env[i] + 5), EXIT_SUCCESS);
	}
	if (chdir(dir) == 0)
	{
		if (find_var(d->env, "OLDPWD"))
			update_oldpwd(d);
		free(d->pwd);
		m_get_pwd(d);
		if (find_var(d->env, "PWD"))
			update_pwd(d);
		return (EXIT_SUCCESS);
	}
	perror(dir);
	return (g_ret = 1, EXIT_FAILURE);
}
