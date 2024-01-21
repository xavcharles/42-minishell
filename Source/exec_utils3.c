/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maderuel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:29:42 by maderuel          #+#    #+#             */
/*   Updated: 2024/01/21 17:51:14 by maderuel         ###   ########.fr       */
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
