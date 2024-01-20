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

int		is_charset(char c, char *set)
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

// int	cmd_count(char const *s, char *set)
// {
// 	int		i;
// 	int		w;
// 	int		in_quote;
// 	char	open_quote;

// 	i = 0;
// 	w = 0;
// 	in_quote = 0;
// 	open_quote = 0;
// 	if (!s)
// 		return (0);
// 	while (s[i])
// 	{
// 		if (is_charset(s[i], set) && !in_quote)
// 			i++;
// 		else
// 		{
// 			while (s[i] && (!is_charset(s[i], set) || in_quote))
// 			{
// 				if ((s[i] == '\'' || s[i] == '"') && !in_quote)
// 				{
// 					open_quote = s[i];
// 					in_quote = 1;
// 				}
// 				else if (in_quote == 1 && s[i] == open_quote)
// 				{
// 					open_quote = 0;
// 					in_quote = 0;
// 				}
// 				i++;
// 			}
// 			w++;
// 		}
// 	}
// 	return (w);
// }

void	cmd_count_loop(char *s, int *i, char *set, int *inquote)
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
			cmd_count_loop(s, &i, set, &inquote);
			w++;
		}
	}
	return (w);
}
void	rev_ms_split_if(char **s, int *i, int *in_quote)
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

char	**ms_split_loop(char *s, int *i, char *set, int *inquote)
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

char	**check_if_unclosed(char **strs, int inquote)
{
	if (inquote == 1)
	{
		printf("Error : unclosed quote\n");
		clean_strs(strs, 0, 0);
		return (NULL);
	}
	return (strs);
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
	return (check_if_unclosed(strs, inquote));
}

// char	**ms_split(char *s, char *set)
// {
// 	int		w;
// 	int		i;
// 	int		start;
// 	int		in_quote;
// 	char	open_quote;
// 	char	**strs;

// 	strs = malloc(sizeof(char *) * (cmd_count(s, set) + 1));
// 	if (!strs)
// 		return (NULL);
// 	i = 0;
// 	w = 0;
// 	in_quote = 0;
// 	open_quote = 0;
// 	while (s && s[i])
// 	{
// 		if (is_charset(s[i], set))
// 			i++;
// 		else
// 		{
// 			start = i;
// 			while (s[i] && (!is_charset(s[i], set) || in_quote))
// 			{
// 				if ((s[i] == '\'' || s[i] == '"') && !in_quote)
// 				{
// 					open_quote = s[i];
// 					in_quote = 1;
// 				}
// 				else if (in_quote == 1 && s[i] == open_quote && i != start)
// 				{
// 					open_quote = 0;
// 					in_quote = 0;
// 				}
// 				i++;
// 			}
// 			strs[w] = ft_substr(s, start, i - start);
// 			w++;
// 		}
// 	}
// 	strs[w] = NULL;
// 	if (in_quote == 1)
// 	{
// 		printf("Error : unclosed quote\n");
// 		clean_strs(strs, 0, 0);
// 		return (0);
// 	}
// 	return (strs);
// }

int	rev_ms_split_else(char **s, char **strs, int in_quote, int *w)
{
	int	i;

	i = 0;
	while (s[i] && is_charset(s[i], set) && !in_quote)
		i++;
	strs[*w] = ft_substr(s, 0, i);
	if (!strs[*w])
		return (clean_strs(strs, 0, 0), -1);
	(*w)++;
	strs[*w] = NULL;
	return (i);
}

char	**rev_ms_split(char *s, char *set)
{
	int		w;
	int		i;
	int		in_quote;
	int		start;
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
			start = i;
			i += rev_ms_split_else(s, strs, in_quote, &w);
			if (i < start)
				return (1);
		}
	}
	return (strs);
}
