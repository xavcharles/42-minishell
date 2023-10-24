/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:48:26 by xacharle          #+#    #+#             */
/*   Updated: 2022/11/17 17:45:27 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = ft_strlen(s);
	while (len >= 0)
	{
		if (s[len] == (unsigned char)c)
			return ((char *)s + len);
		len--;
	}
	return (0);
}
/*
int	main()
{
	char	test[5] = "test";

	printf("strrchr(test, 't') = %s\n", strrchr(test, 't' + 512));
	printf("ft_strrchr(test, 't') = %s\n", ft_strrchr(test, 't' + 512));
	return (0);
}
*/
