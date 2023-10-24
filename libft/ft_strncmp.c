/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:31:44 by xacharle          #+#    #+#             */
/*   Updated: 2022/11/18 20:03:20 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	a;
	unsigned char	b;

	i = 0;
	a = s1[i];
	b = s2[i];
	if (n == 0)
		return (0);
	while ((a == b) && (a || b) && (i < n - 1))
	{
		i++;
		a = s1[i];
		b = s2[i];
	}
	return (a - b);
}
/*
int	main()
{
	printf("%d\n", ft_strncmp("","",5));
	printf("%d\n", strncmp("","",5));
	return (0);
}
*/
