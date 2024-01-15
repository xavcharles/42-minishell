/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maderuel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:30:39 by maderuel          #+#    #+#             */
/*   Updated: 2024/01/15 13:30:49 by maderuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(t_data *d, int n)
{
	if (d)
	{
		clean_data(d);
		if (d->paths)
			clean_strs(d->paths, 0, 0);
		if (d->env)
			clean_strs(d->env, 0, 0);
		if (d->input)
			free(d->input);
		rl_clear_history();
		free(d);
	}
	exit(n);
}
