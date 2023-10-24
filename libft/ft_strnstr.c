/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:17:01 by xacharle          #+#    #+#             */
/*   Updated: 2022/11/15 15:52:49 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	lstr;
	size_t	ltf;

	i = 0;
	if (big == NULL)
		lstr = 0;
	else
		lstr = ft_strlen(big);
	ltf = ft_strlen(little);
	if (ltf == 0)
		return ((char *)big);
	while (i < (lstr - ltf + 1) && i < len)
	{
		if ((big[i] == little[0]))
		{
			if (!(ft_strncmp(big + i, little, ltf)) && i <= len - ltf)
			{
				return ((char *)big + i);
			}
		}
		i++;
	}
	return (0);
}
/*
#include <stdlib.h>
#include <stdio.h>
#include <bsd/string.h>

int	main(int argc, char *argv[])
{
	const char *big = NULL;
	const char *little = NULL;
	//size_t len = atoi(argv[3]);
	size_t len = 0;
	char *res;

	//res = ft_strnstr(big, little, len);
	res = strnstr(big, little, len);
	printf("strnstr(%s, %s, %ld) = %s\n", big, little, len, res);
	//printf("ft_strnstr(%s, %s, %ld) = %s\n", big, little, len, res);
	return (0);
}
*/
