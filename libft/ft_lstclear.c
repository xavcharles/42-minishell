/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 02:53:28 by xacharle          #+#    #+#             */
/*   Updated: 2022/11/19 15:35:57 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*cur;

	while (*lst)
	{
		cur = (*lst)->next;
		(*del)((*lst)->content);
		free(*lst);
		*lst = cur;
	}
	*lst = NULL;
}
/*
void	f_del(void *d)
{
	free(d);
}

int	main(int argc, char *argv[])
{
	char	*a = "test2";
	char	*b = "test1";
	t_list	*l = ft_lstnew(a);
	t_list	*n = ft_lstnew(b);
	ft_lstadd_back(&l, n);
	ft_lstclear(&l, f_del);
	if (!l)
	{
		printf("ca marche\n");
		return (0);
	}
	printf("oups\n", n);
//	free(n);
//	free(l);
	return (0);
}
*/
