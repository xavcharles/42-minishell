/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 00:24:03 by xacharle          #+#    #+#             */
/*   Updated: 2022/11/19 14:51:55 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*cur;

	if (lst == NULL)
		return (0);
	cur = lst;
	i = 1;
	while (cur -> next)
	{
		cur = cur -> next;
		i++;
	}
	return (i);
}
/*
int	main(int argc, char *argv[])
{
	char	*a = argv[1];
	char	*b = argv[2];
	t_list	*l = ft_lstnew(a);
	t_list	*n = ft_lstnew(b);
	ft_lstadd_back(&l, n);
	printf("%d\n", ft_lstsize(l));
	return (0);
}
*/
