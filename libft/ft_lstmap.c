/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:16:34 by xacharle          #+#    #+#             */
/*   Updated: 2022/11/19 15:32:04 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*cur;
	t_list	*beg;

	beg = NULL;
	cur = lst;
	while (cur)
	{
		new = ft_lstnew((*f)(cur -> content));
		if (!new)
		{
			ft_lstclear(&beg, (*del));
			return (NULL);
		}
		ft_lstadd_back(&beg, new);
		cur = cur -> next;
	}
	return (beg);
}
/*
void	*f_map(void *content)
{
	(void)content;
	return ("ok");
}

void	f_del(void *d)
{
	free(d);
}

int	main(int argc, char *argv[])
{
	char	*a = argv[1];
	char	*b = argv[2];
	t_list	*l = ft_lstnew(a);
	t_list	*n = ft_lstnew(b);
	t_list	*m;
	ft_lstadd_back(&l, n);
	m = ft_lstmap(l, f_map, f_del);
	printf("%s\n", m -> content);
	printf("%s\n", m->next->content);
	return (0);
}
*/
