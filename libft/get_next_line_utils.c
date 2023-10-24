/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:21:57 by xacharle          #+#    #+#             */
/*   Updated: 2023/05/10 17:28:29 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_len(char *str, char c)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != c)
		i++;
	return (i);
}

int	is_line(char *str, int l)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (i < l && str[i])
	{	
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
