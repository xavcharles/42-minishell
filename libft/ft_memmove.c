/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:44:40 by xacharle          #+#    #+#             */
/*   Updated: 2022/11/18 20:05:52 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*tdest;
	unsigned char	*tsrc;

	tdest = (unsigned char *)dest;
	tsrc = (unsigned char *)src;
	if (tsrc < tdest)
		while (n--)
			tdest[n] = tsrc[n];
	else if (tsrc > tdest)
	{
		i = 0;
		while (i < n)
		{
			tdest[i] = tsrc[i];
			i++;
		}
	}
	return (dest);
}
