/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:24:16 by xacharle          #+#    #+#             */
/*   Updated: 2024/01/22 12:57:29 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_stxerr(char c1, char c2)
{
	if (!c2)
	{
		ft_dprintf(2, "minishell: syntax error near unexpected token");
		ft_dprintf(2, " `%c'\n", c1);
		return (1);
	}
	else
	{
		ft_dprintf(2, "minishell: syntax error near unexpected token `%c", c1);
		ft_dprintf(2, "%c'\n", c2);
		return (1);
	}
	return (0);
}
