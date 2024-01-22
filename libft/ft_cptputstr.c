/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cptputstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:33:50 by xacharle          #+#    #+#             */
/*   Updated: 2024/01/22 12:42:01 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_cptputstr(int fd, va_list args, int *cpt)
{
	char	*str;

	str = va_arg(args, char *);
	if (!str)
		*cpt += 6;
	else
		*cpt += ft_strlen(str);
	ft_putstr_fd(str, fd);
}
