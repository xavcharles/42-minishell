/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:20:19 by xacharle          #+#    #+#             */
/*   Updated: 2022/11/19 14:30:04 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new -> next = *lst;
	*lst = new;
}
/*
int	main(int argc, char *argv[])
{
	char	*a = argv[1];
	char	*b = argv[2];
	t_list	*l = lstnew(a);
	t_list	*n = lstnew(b);
	ft_lstadd_front(&l, n);
	printf("%s\n", (char *)l->content);
	printf("%s\n", (char *)l->next->content);
	free(l->next);
	free(n);
	return (0);
}
*/
