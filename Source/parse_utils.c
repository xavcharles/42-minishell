/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:27:31 by xacharle          #+#    #+#             */
/*   Updated: 2024/01/20 18:27:33 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ms_split_loop(char *s, int *i, char *set, int *in_quote)
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
	return (ft_substr(s, start, *i - start));
}

char	**ms_split(char *s, char *set)
{
	int		w;
	int		i;
	int		in_quote;
	char	**strs;

	strs = malloc(sizeof(char *) * (cmd_count(s, set) + 1));
	if (!strs)
		return (NULL);
	i = 0;
	w = 0;
	in_quote = 0;
	while (s && s[i])
	{
		if (is_charset(s[i], set) && !in_quote)
			i++;
		else
		{
			strs[w] = ms_split_loop(s, &i, set, &in_quote);
			if (!strs[w])
				return (clean_strs(strs, 0, 0), NULL);
			w++;
		}
	}
	strs[w] = NULL;
	return (check_if_unclosed(strs, in_quote));
}

void	rev_ms_split_if(char const *s, int *i, int *in_quote)
{
	char	open_quote;

	open_quote = 0;
	if ((s[*i] == '\'' || s[*i] == '"') && !*in_quote)
	{
		open_quote = s[*i];
		*in_quote = 1;
	}
	else if (s[*i] == open_quote)
	{
		open_quote = 0;
		*in_quote = 0;
	}
	(*i)++;
}

char	*rev_ms_split_else(char *s, int *i, char *set, int in_quote)
{
	int		start;
	char	*str;

	start = *i;
	while (s[*i] && is_charset(s[*i], set) && !in_quote)
		(*i)++;
	str = ft_substr(s, start, *i - start);
	if (!str)
		return (NULL);
	return (str);
}

char	**rev_ms_split(char *s, char *set)
{
	int		w;
	int		i;
	int		in_quote;
	char	**strs;

	strs = malloc(sizeof(char *) * (sep_count(s, set) + 1));
	if (!strs)
		return (NULL);
	i = 0;
	w = 0;
	in_quote = 0;
	while (s && s[i])
	{
		if (s[i] && (!is_charset(s[i], set) || in_quote))
			rev_ms_split_if(s, &i, &in_quote);
		else
		{
			strs[w] = rev_ms_split_else(s, &i, set, in_quote);
			if (!strs[w])
				return (clean_strs(strs, 0, 0), NULL);
			w++;
		}
	}
	strs[w] = NULL;
	return (strs);
}
