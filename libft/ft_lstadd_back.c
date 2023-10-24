/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 01:49:23 by xacharle          #+#    #+#             */
/*   Updated: 2022/11/19 14:29:24 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*cur;

	cur = *lst;
	if (cur == NULL)
		*lst = new;
	else
	{
		while (cur -> next)
			cur = cur -> next;
		cur -> next = new;
	}
}
/*
int	main(int argc, char *argv[])
{
	char	*a = argv[1];
	char	*b = argv[2];
	t_list	*l = ft_lstnew(a);
	t_list	*n = ft_lstnew(b);
	ft_lstadd_back(&l, n);
	printf("%s\n", (char *)l->next->content);
	free(n);
	free(l);
	return (0);
}
*/
