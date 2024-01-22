/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:09:06 by xacharle          #+#    #+#             */
/*   Updated: 2024/01/22 12:40:48 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base_u(int fd, unsigned int nb, char *base, int *cpt)
{	
	unsigned int		base_len;

	base_len = ft_strlen(base);
	if (nb >= base_len)
		ft_putnbr_base_u(fd, nb / base_len, base, cpt);
	ft_putchar_fd(base[nb % base_len], fd);
	*cpt += 1;
}

void	ft_putnbr_base_l(int fd, long nbr, char *base, int *cpt)
{	
	unsigned int	base_len;
	long			nb;

	base_len = ft_strlen(base);
	nb = nbr;
	if (nb < 0)
	{
		nb = nb * (-1);
		write(fd, "-", 1);
		*cpt += 1;
	}
	if (nb >= base_len)
		ft_putnbr_base_l(fd, nb / base_len, base, cpt);
	ft_putchar_fd(base[nb % base_len], fd);
	*cpt += 1;
}

void	ft_printpoint(int fd, va_list args, int *cpt)
{
	unsigned long long		test;
	long long				p;

	p = va_arg(args, long long);
	test = p;
	if (p != 0)
	{
		ft_putstr_fd("0x", fd);
		*cpt += 2;
		if (test == ULONG_MAX)
		{
			write(fd, "ffffffffffffffff", 16);
			*cpt += 16;
		}
		else
			ft_putnbr_base_p(fd, p, "0123456789abcdef", cpt);
	}
	else
	{
		ft_putstr_fd("(nil)", fd);
		*cpt += 5;
	}
}

void	check_arg(int fd, char c, va_list args, int *cpt)
{
	if (c == 'c')
	{
		ft_putchar_fd(va_arg(args, int), fd);
		*cpt += 1;
	}
	else if (c == 's')
		ft_cptputstr(fd, args, cpt);
	else if (c == 'p')
		ft_printpoint(fd, args, cpt);
	else if (c == 'd')
		ft_putnbr_base_l(fd, va_arg(args, int), "0123456789", cpt);
	else if (c == 'i')
		ft_putnbr_base_l(fd, va_arg(args, int), "0123456789", cpt);
	else if (c == 'u')
		ft_putnbr_base_u(fd, va_arg(args, unsigned int), "0123456789", cpt);
	else if (c == 'x')
		ft_putnbr_base_u(fd, va_arg(args, unsigned int), "0123456789abcdef", cpt);
	else if (c == 'X')
		ft_putnbr_base_u(fd, va_arg(args, unsigned int), "0123456789ABCDEF", cpt);
	else if (c == '%')
	{
		ft_putchar_fd('%', fd);
		*cpt += 1;
	}
}

int	ft_dprintf(int fd, const char *s, ...)
{
	int		cpt;
	int		i;
	va_list	args;

	va_start(args, s);
	i = 0;
	cpt = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			check_arg(fd, s[++i], args, &cpt);
			if (s[i])
				i++;
		}
		else
		{
			ft_putchar_fd(s[i++], fd);
			cpt++;
		}
	}
	return (cpt);
}
/*
int	main()
{
	char a, b, c, d;
	char	*h = NULL;
	int	e, f, g, i;
	a = 0x74;
	b = 'e';
	c = 's';
	d = 't';
	e = 0xffffffff;
	f = 2;
	g = 3;
	i = -1;
	printf("LONGMAX = %ld\n-LONGMAX = %ld\n", LONG_MAX, LONG_MIN);
//	printf("printf : %010d\n", 123456);
//	printf("printf : %c %c %c %c %d %d %d %s %p %u %x %X %%\n", a, b, c, d, e, 
//	f, g, h, h, i, e, i);
	printf("printf = %d\n", printf("printf : %c %c %c %c %d %d %d %s %p %u %x 
	%X %%\n", a, b, c, d, e, f, g, h, LONG_MIN, i, LONG_MAX, i));
//	ft_printf("ft_printf : %c %c %c %c %d %d %d %s %p %u %x %X %%\n", a, b, c,
//	d, e, f, g, h, h, i, e, i);
	ft_printf("ft_printf = %d\n", ft_printf("ft_printf : %c %c %c %c %d %d %d 
	%s %p %u %x %X %%\n", a, b, c, d, e, f, g, h, LONG_MIN, i, LONG_MAX, i));
//	ft_printf("%c\n", a);
	return (0);
}
*/
