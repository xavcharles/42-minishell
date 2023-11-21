/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:26:13 by xacharle          #+#    #+#             */
/*   Updated: 2022/11/10 17:48:40 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	if (c == 0)
		return ((char *)s + i);
	return (0);
}
/*
int main()
{
	char	test[5] = "test";
	
	printf("strchr(test, 't') = %s\n", strchr(test, 't' + 512));
	printf("ft_strchr(test, 't') = %s\n", ft_strchr(test, 't' + 512));
	return (0);
}
*/
