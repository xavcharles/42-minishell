/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:36:52 by xacharle          #+#    #+#             */
/*   Updated: 2022/11/15 01:07:34 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	void	*p;

	p = s;
	while (n--)
	{
		if (*((char *)s) != 0)
			*((char *)s) = 0;
		s++;
	}
	s = p;
}
/*
int	main()
{
	char	test[7] = "lalala";
   
	ft_bzero(test, 4);
	printf("%s\n", test);
	printf("%s\n", test + 4);
	return (0);
}
*/
