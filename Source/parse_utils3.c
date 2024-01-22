/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:27:48 by xacharle          #+#    #+#             */
/*   Updated: 2024/01/22 13:11:00 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_charset(char c, char *set)
{
	int	i;

	i = 0;
	if (c == 0)
		return (1);
	while (set[i])
	{
		if (c == set[i++])
			return (1);
	}
	return (0);
}

void	cmd_count_loop(char const *s, int *i, char *set, int *in_quote)
{
	int		start;
	char	open_quote;

	start = *i;
	open_quote = 0;
	while (s[*i] && (!is_charset(s[*i], set) || *in_quote))
	{
		if ((s[*i] == '\'' || s[*i] == '"') && !*in_quote)
		{
			open_quote = s[*i];
			*in_quote = 1;
		}
		else if (*in_quote == 1 && s[*i] == open_quote && *i != start)
		{
			open_quote = 0;
			*in_quote = 0;
		}
		(*i)++;
	}
}

int	cmd_count(char const *s, char *set)
{
	int		i;
	int		w;
	int		in_quote;

	i = 0;
	w = 0;
	in_quote = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (is_charset(s[i], set) && !in_quote)
			i++;
		else
		{
			cmd_count_loop(s, &i, set, &in_quote);
			w++;
		}
	}
	return (w);
}

int	sep_count(char const *s, char *set)
{
	int		i;
	int		w;
	int		in_quote;

	i = 0;
	w = 0;
	in_quote = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] && (!is_charset(s[i], set) || in_quote))
			rev_ms_split_if(s, &i, &in_quote);
		else
		{
			while (s[i] && is_charset(s[i], set) && !in_quote)
				i++;
			w++;
		}
	}
	return (w);
}

char	**check_if_unclosed(char **strs, int inquote)
{
	if (inquote == 1)
	{
		ft_dprintf(2, "Error : unclosed quote\n");
		clean_strs(strs, 0, 0);
		return (NULL);
	}
	return (strs);
}
