/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:19:09 by xacharle          #+#    #+#             */
/*   Updated: 2022/11/18 20:06:05 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;

	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (len-- && start < ft_strlen(s))
		str[i++] = s[start++];
	str[i] = 0;
	return (str);
}
/*
int	main()
{
	char *s = "test";
	unsigned int start = 4;
	size_t len = 4;
	printf("substr donne : %s\n", ft_substr(s, start, len));
	return (0);
}
*/
