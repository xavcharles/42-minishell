/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:35:37 by xacharle          #+#    #+#             */
/*   Updated: 2022/11/15 15:59:17 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	if (nmemb * size > 2147483647)
		return (NULL);
	p = malloc(nmemb * size);
	if (!p)
		return (NULL);
	if (size == 0 || nmemb == 0)
		return (p);
	else
	{
		ft_bzero(p, nmemb * size);
		return (p);
	}
}
/*
int	main()
{
	int nmemb = 2147483647;
	//int nmemb = 0;
	int size = 1;
	char *test;
	//test = calloc(nmemb, size);
	printf("%p", ft_calloc(nmemb, size));
	return (0);
}
*/
