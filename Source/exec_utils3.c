/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maderuel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:29:42 by maderuel          #+#    #+#             */
/*   Updated: 2024/01/21 17:30:11 by maderuel         ###   ########.fr       */
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
