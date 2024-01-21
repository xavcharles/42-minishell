/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:55:10 by xacharle          #+#    #+#             */
/*   Updated: 2024/01/20 16:55:33 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	sign_after_sign(char *str, int *i)
{
	while (str[*i] == '<' && *i < 2)
		(*i)++;
	if (*i == 2)
		return (print_stxerr('<', '<'));
	if (*i == 1 && is_charset(str[*i], "&>"))
		return (print_stxerr('<', str[*i]));
	else if (*i == 1)
		return (print_stxerr('<', 0));
	while (str[*i] == '|' && *i < 2)
		(*i)++;
	if (*i == 2)
		return (print_stxerr('|', '|'));
	if (*i == 1 && str[*i] == '&')
		return (print_stxerr('|', '&'));
	else if (*i == 1)
		return (print_stxerr('|', 0));
	while (str[*i] == '>' && *i < 2)
		(*i)++;
	if (*i == 2)
		return (print_stxerr('>', '>'));
	if ((*i == 1) && is_charset(str[*i], "&|"))
		return (print_stxerr('>', str[*i]));
	else if (*i == 1)
		return (print_stxerr('>', 0));
	return (0);
}

int	check_morethan(char *str, int *i)
{
	int	n;

	*i = 0;
	n = 0;
	while (str[*i] && str[*i] == '>' && *i < 2)
		(*i)++;
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
	if (!str[*i])
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	if (sign_after_sign(str + *i, &n))
	{
		*i += n;
		return (1);
	}
	*i += n;
	return (0);
}

int	check_lessthan(char *str, int *i)
{
	int	n;

	*i = 0;
	n = 0;
	while (str[*i] && str[*i] == '<' && *i < 2)
		(*i)++;
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
	if (!str[*i])
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	if (sign_after_sign(str + *i, &n))
	{
		*i += n;
		return (1);
	}
	*i += n;
	return (0);
}

int	input_check2(char *str, int *i)
{
	if (*str == '(' || *str == ')' || *str == '[' || *str == ']')
		return (print_stxerr(*str, 0), 1);
	else if (*str == '<')
	{
		if (check_lessthan(str, i))
			return (1);
	}
	else if (*str == '>')
	{
		if (check_morethan(str, i))
			return (1);
	}
	else if (*str == '&')
	{
		if (check_esp(str, i))
			return (1);
	}
	else if (*str == '|')
	{
		if (check_pipe(str, i))
			return (1);
	}
	return (0);
}

int	input_check(t_data *d)
{
	int		i;
	char	*str;

	str = d->input;
	while (*str)
	{
		i = 1;
		if (!is_charset(*str, "()[]\"'&|><"))
			str++;
		else
		{
			printf("str = %s\n", str);
			if (*str == '"')
				while (*(++str) && *str != '"')
					;
			if (*str == '\'')
				while (*(++str) && *str != '\'')
					;
			if (input_check2(str, &i))
				return (1);
			str += i;
		}
	}
	return (0);
}
