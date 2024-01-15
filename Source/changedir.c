/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changedir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maderuel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:24:21 by maderuel          #+#    #+#             */
/*   Updated: 2024/01/15 14:24:32 by maderuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd_builtin(t_data *d, int cc)
{
	char	*dir;

	dir = d->cmd[cc].cmd_arg[1];
	if (chdir(dir) == 0)
		return (EXIT_SUCCESS);
	perror(dir);
	return (EXIT_FAILURE);
}
