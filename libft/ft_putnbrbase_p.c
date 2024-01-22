/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrbase_p.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:23:49 by xacharle          #+#    #+#             */
/*   Updated: 2024/01/22 12:39:00 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base_p(int fd, long long nbr, char *base, int *cpt)
{
	unsigned int	base_len;
	long long		nb;

	base_len = ft_strlen(base);
	nb = nbr;
	if (nb < 0)
	{
		if (nb == LONG_MIN)
		{
			write(fd, "8000000000000000", 16);
			*cpt += 16;
			return ;
		}
		nb = nb * (-1);
		write(fd, "-", 1);
		*cpt += 1;
	}
	if (nb >= base_len)
		ft_putnbr_base_l(fd, nb / base_len, base, cpt);
	ft_putchar_fd(base[nb % base_len], fd);
	*cpt += 1;
}
