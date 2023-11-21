/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:29:54 by xacharle          #+#    #+#             */
/*   Updated: 2022/11/14 12:00:37 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	char	*str;

	size = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	str[0] = 0;
	ft_strlcat(str, s1, size + 1);
	ft_strlcat(str, s2, size + 1);
	return (str);
}
/*
int     main(int argc, char *argv[])
{
	char s1[1] = "";
	char s2[1] = "";
	printf("ft_strjoin(%s, %s) = %s\n", s1, s2, ft_strjoin(s1, s2));
	return (0);
}
*/
