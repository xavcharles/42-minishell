/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:56:06 by xacharle          #+#    #+#             */
/*   Updated: 2022/11/19 15:42:19 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*cur;

	cur = lst;
	while (cur)
	{
		(*f)(cur -> content);
		cur = cur -> next;
	}
}
/*
void	f_ok(void *content)
{
	char *s = content;
	s[0] = 'o';
	s[1] = 'k';
}

int	main(int argc, char *argv[])
{
	char	*a = argv[1];
	char	*b = argv[2];
	t_list	*l = ft_lstnew(a);
	t_list	*n = ft_lstnew(b);

	ft_lstadd_back(&l, n);
	ft_lstiter(l, f_ok);
	printf("%s\n", l->content);
	printf("%s\n", l->next->content);
	return (0);
}
*/
