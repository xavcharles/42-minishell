/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maderuel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:24:51 by maderuel          #+#    #+#             */
/*   Updated: 2023/12/05 16:02:43 by maderuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(t_cmd *cmd, char **n_env)
{

}

int	ft_export(t_cmd *cmd, char **o_env)
{
	int		i;
	char	**n_env;

	i = 0;
	while (o_env[i])
		i++;
	n_env = malloc(sizeof(char *) * (i + 1));
	if (!n_env)
		return (1);
	i = 0;
	while (o_env[i])
	{
		n_env[i] = ft_strdup(o_env[i]);
		i++;
	}
	n_env[i + 1] = ft_strdup(cmd->cmds[1]);
	return (0);
}

char	**env_alloc(char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * i);
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
			return (NULL);
		i++;
	}
	return (new_env);
}
