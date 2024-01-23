/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changedir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:24:21 by maderuel          #+#    #+#             */
/*   Updated: 2024/01/23 01:15:47 by xacharle         ###   ########.fr       */
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

int	sub_cd(t_data *d, int cc, char *dir)
{
	(void) cc;
	if (find_var(d->env, "OLDPWD"))
		update_oldpwd(d);
	m_get_pwd(d);
	if (find_var(d->env, "PWD"))
		update_pwd(d);
	if (dir && dir != d->cmd[cc].cmd_arg[1])
		free(dir);
	return (EXIT_SUCCESS);
}

int	cd_home(t_data *d)
{
	int	i;

	i = -1;
	while (d->env[++i])
		if (!ft_strncmp(d->env[i], "HOME", 4))
			break ;
	if (!d->env[i])
		return (ft_putstr_fd("HOME not set\n", 2), EXIT_FAILURE);
	return (chdir(d->env[i] + 5), m_get_pwd(d), EXIT_SUCCESS);
}

int	cd_builtin(t_data *d, int cc)
{
	char	*dir;
	char	*tmp;

	if (strs_len(d->cmd[cc].cmd_arg) > 2)
		return (g_ret = 1, ft_dprintf(2, " too many arguments\n"));
	dir = d->cmd[cc].cmd_arg[1];
	if (!dir || !ft_strcmp(dir, "~"))
		return (cd_home(d));
	if (dir[0] == '~')
	{
		tmp = ft_strjoin(getenv("HOME"), ft_strchr(dir, '~') + 1);
		dir = ft_strdup(tmp);
		free(tmp);
	}
	if (chdir(dir) == 0)
		return (sub_cd(d, cc, dir), 0);
	perror(dir);
	return (g_ret = 1, EXIT_FAILURE);
}
