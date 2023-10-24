/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 00:34:57 by xacharle          #+#    #+#             */
/*   Updated: 2022/11/19 14:57:22 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*cur;

	cur = lst;
	if (lst == NULL || lst -> next == NULL)
		return (lst);
	while (cur -> next)
		cur = cur -> next;
	return (cur);
}
/*
int	main(int argc, char *argv[])
{
	char	*a = argv[1];
	char	*b = argv[2];
	t_list	*l = ft_lstnew(a);
	t_list	*n = ft_lstnew(b);
	t_list	*last;
	ft_lstadd_back(&l, n);
	last = ft_lstlast(l);
	printf("%s\n", last -> content);
	return (0);
}
*/
