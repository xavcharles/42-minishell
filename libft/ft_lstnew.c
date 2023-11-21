/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:38:16 by xacharle          #+#    #+#             */
/*   Updated: 2022/11/19 14:45:38 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*lst;

	lst = malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	if (content)
		lst -> content = content;
	else
		lst -> content = NULL;
	lst -> next = NULL;
	return (lst);
}
/*
t_list  *ft_lstnew(void *content)
{
    t_list  *lst;

    lst = malloc(sizeof(t_list));
    if (!lst)
        return (NULL);
    if (content)
    {
        lst -> content = malloc(sizeof(unsigned char) * ft_strlen(content));
        if (!(lst -> content))
            return (NULL);
        ft_memmove(lst -> content, content, ft_strlen(content));
    }
    else
        lst -> content = NULL;
    lst -> next = NULL;
    return (lst);
}
*/
/*
int	main(int argc, char *argv[])
{
	char	*a = argv[1];
	t_list	*l = ft_lstnew(a);
	printf("%s\n", l -> content);
	if (!(l -> next))
		printf("ca marche\n");
	return (0);
}
*/
