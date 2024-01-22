/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:54:42 by xacharle          #+#    #+#             */
/*   Updated: 2024/01/20 16:54:45 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_first(char *input)
{
	int	i;

	i = 0;
	if (input[0] == '|')
	{
		while (input[i] && input[i] == '|' && i < 2)
			i++;
		if (i == 2)
			return (print_stxerr('|', '|'));
		if (i == 1 && input[i] == '&')
			return (print_stxerr('|', '&'));
		else
			return (print_stxerr('|', 0));
	}
	else if (input[0] == '&')
	{
		while (input[i] && input[i] == '&' && i < 2)
			i++;
		if (i == 2)
			return (print_stxerr('&', '&'));
		else
			return (print_stxerr('&', 0));
	}
	return (0);
}

int	check_firstbis(char *input)
{
	int	i;

	i = 0;
	if (input[0] == ';')
	{
		while (input[i] && input[i] == ';' && i < 2)
			i++;
		if (i == 2)
			return (print_stxerr(';', ';'));
		if (i == 1 && input[i] == '&')
			return (print_stxerr(';', '&'));
		else
			return (print_stxerr(';', 0));
	}
	return (0);
}

int	check_bis(char *str, int *i)
{
	*i = 0;
	while (str[*i] && str[*i] == ';' && *i < 2)
		(*i)++;
	if (*i == 2)
		return (print_stxerr(';', ';'));
	else if (*i == 1 && str[*i] == '&')
		return (print_stxerr(';', '&'));
	else if (*i == 1)
		return (print_stxerr(';', 0));
	return (0);
}

int	check_pipe(char *str, int *i)
{
	int	n;

	*i = 0;
	n = 0;
	while (str[*i] && str[*i] == '|' && *i < 2)
		(*i)++;
	if (*i == 2)
		return (print_stxerr('|', '|'), g_ret = 127, 1);
	else
	{
		while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
			(*i)++;
		while (str[*i + n] == '|' && n < 2)
			n++;
		if (n == 2)
			return (print_stxerr('|', '|'), g_ret = 127, 1);
		if (n == 1 && str[*i + n] == '&')
			return (print_stxerr('|', '&'), g_ret = 127, 1);
		if (n == 1)
			return (print_stxerr('|', 0), g_ret = 127, 1);
	}
	return (0);
}

int	check_esp(char *str, int *i)
{
	*i = 0;
	while (str[*i] && str[*i] == '&' && *i < 2)
		(*i)++;
	if (*i == 2)
		return (print_stxerr('&', '&'));
	if (*i == 1)
		return (print_stxerr('&', 0));
	return (0);
}
