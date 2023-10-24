/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:01:25 by xacharle          #+#    #+#             */
/*   Updated: 2022/11/18 20:04:33 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ischarset(char const *set, unsigned char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	char	*str;

	while (ischarset(set, *s1))
		s1++;
	i = ft_strlen(s1);
	while (ischarset(set, s1[i - 1]) && i != 0)
		i--;
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		return (NULL);
	str[i] = 0;
	while (i--)
		str[i] = s1[i];
	return (str);
}
/*
int	main(int argc, char *argv[])
{
	//char *s1 = argv[1];
	//char *set = argv[2];
	
	char	*s1 = "   \t  \n\n \t\t  \n\n\nHel
	lo \t  Please\n Trim me !\n   \n \n \t\t\n  ";
	char	*set = " \n\t";
	printf("ft_strtrim(%s, %s) = %s\n", s1, set, ft_strtrim(s1, set));
	return (0);
}
*/
