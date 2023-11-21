/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:58:15 by xacharle          #+#    #+#             */
/*   Updated: 2022/11/15 00:57:44 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n)
	{
		if (*((unsigned char *)s + i) == (unsigned char)c)
			return ((void *)s + i);
		i++;
	}
	return (0);
}
/*
int	main()
{
	char	test[5] = "test";

	printf("memchr(test, 't', 4) = %s\n", (char *)memchr(test, 't' + 512, 1));
	printf("ft_memchr(test, 't', 4) = %s\n", (char *)ft_memchr(test, 't' + 512, 1));
	return (0);
}
*/
