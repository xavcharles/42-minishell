/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:05:50 by xacharle          #+#    #+#             */
/*   Updated: 2022/11/15 02:03:13 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dest_len;
	size_t	src_len;

	dest_len = ft_strlen(dest);
	i = dest_len;
	src_len = ft_strlen(src);
	if (dest_len >= size)
		return (size + src_len);
	j = 0;
	while ((j < (size - dest_len - 1)) && (src[j] != '\0'))
		dest[i++] = src[j++];
	dest[i] = '\0';
	return (src_len + dest_len);
}
/*
#include <bsd/string.h>

int	main()
{
	char *dest = 0;
	char *src = "";
	size_t size = 5;
	printf("%ld\n", ft_strlcat(dest, src, size));
	//printf("%ld\n", strlcat(dest, src, size));
}
*/
