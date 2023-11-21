/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:40:36 by xacharle          #+#    #+#             */
/*   Updated: 2022/11/10 16:09:08 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	len;

	len = ft_strlen(s);
	dup = malloc(len * sizeof(char) + 1);
	if (!dup)
		return (NULL);
	dup[len] = 0;
	while (len--)
		dup[len] = s[len];
	return (dup);
}
