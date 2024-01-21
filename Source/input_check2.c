/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:24:16 by xacharle          #+#    #+#             */
/*   Updated: 2024/01/20 17:24:16 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_stxerr(char c1, char c2)
{
	if (!c2)
	{
		(printf("minishell: syntax error near unexpected token"));
		(printf(" `%c'\n", c1));
		return (1);
	}
	else
	{
		printf("minishell: syntax error near unexpected token `%c", c1);
		printf("%c'\n", c2);
		return (1);
	}
	return (0);
}
