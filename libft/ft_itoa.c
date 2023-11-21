/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:59:16 by xacharle          #+#    #+#             */
/*   Updated: 2022/11/18 20:06:30 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nbsize(int n)
{
	int	nb;

	nb = 0;
	if (n == -2147483648)
		return (11);
	if (n <= 0)
	{
		nb++;
		n = -n;
	}
	while (n > 0)
	{
		n /= 10;
		nb++;
	}
	return (nb);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	long	nb;

	nb = n;
	i = ft_nbsize(n);
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		return (NULL);
	if (nb <= 0)
	{
		str[0] = '0';
		if (nb < 0)
			str[0] = '-';
		nb = -nb;
	}
	str[i--] = 0;
	while (nb > 0)
	{
		str[i--] = '0' + nb % 10;
		nb /= 10;
	}
	return (str);
}
/*
int	main(int argc, char *argv[])
{
	char *str;
	int	n = atoi(argv[1]);
	str = ft_itoa(n);
	printf("itoa donne %s\n", str);
	return (0);
}
*/
