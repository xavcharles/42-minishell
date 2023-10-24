/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:48:07 by xacharle          #+#    #+#             */
/*   Updated: 2022/11/19 13:45:25 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	cpt;

	i = 0;
	cpt = 0;
	sign = 1;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	while (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		cpt++;
		i++;
	}
	if (cpt > 1)
		return (0);
	cpt = 0;
	while (ft_isdigit(nptr[i]))
	{
		cpt = (cpt * 10) + nptr[i] - '0';
		i++;
	}
	return (sign * cpt);
}
/*
int	main(int argc, char *argv[])
{
	char	*n = argv[1];
	//char	*n = "\t\v\f\r\n \f- \f\t\n\r    06050";
	int	i1 = atoi(n);
	int	i2 = ft_atoi(n);
}
*/
