/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:32:04 by xacharle          #+#    #+#             */
/*   Updated: 2023/02/03 14:11:45 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (i);
	else
	{
		while (s[i])
			i++;
	}
	return (i);
}
/*
int	main()
{
	char *s = NULL;
	printf("strlen(%s) = %ld\n", s, strlen(s));
	//printf("ft_strlen(%s) = %ld\n", s, ft_strlen(s));
	return (0);
}
*/
