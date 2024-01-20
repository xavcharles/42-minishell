/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:27:38 by xacharle          #+#    #+#             */
/*   Updated: 2024/01/20 18:27:39 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*join_w_space(char *s1, char *s2)
{
	size_t	size;
	char	*str;

	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	str[0] = 0;
	if (s1)
	{
		ft_strlcat(str, s1, size + 1);
		str[ft_strlen(s1) + 1] = 0;
		str[ft_strlen(s1)] = ' ';
	}
	if (s2)
		ft_strlcat(str, s2, size + 1);
	if (s1)
		free(s1);
	return (str);
}

char	*join_w_tab(char *s1, char *s2)
{
	size_t	size;
	char	*str;

	size = ft_strlen(s1) + ft_strlen(s2) + 2;
	str = malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	str[0] = 0;
	if (s1)
	{
		ft_strlcat(str, s1, size + 1);
		str[ft_strlen(s1) + 1] = 0;
		str[ft_strlen(s1)] = ' ';
	}
	if (s2)
		ft_strlcat(str, s2, size + 1);
	str[size] = 0;
	str[size - 1] = '\t';
	if (s1)
		free(s1);
	return (str);
}

void	init_zero(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->cmd_count)
	{
		d->cmd[i].cmd = NULL;
		d->cmd[i].cmd_arg = NULL;
		d->cmd[i].in = NULL;
		d->cmd[i].out = NULL;
		i++;
	}
}

int		quot_count(char *s, char *set)
{
	int		i;
	int		w;
	int		in_quote;
	char	open_quote;

	i = 0;
	w = 0;
	in_quote = 0;
	open_quote = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (is_charset(s[i], set) && !in_quote)
			i++;
		else
		{
			while (s[i] && (!is_charset(s[i], set) || in_quote))
			{
				if (i > 0 && (s[i - 1] == '\'' || s[i - 1] == '"') && !in_quote)
				{
					open_quote = s[i - 1];
					in_quote = 1;
					i--;
				}
				else if (in_quote == 1 && s[i] == open_quote)
				{
					open_quote = 0;
					in_quote = 0;
				}
				i++;
			}
			w++;
		}
	}
	return (w);
}

char	**quot_split(char *s, char *set)
{
	int		w;
	int		i;
	int		start;
	int		in_quote;
	char	open_quote;
	char	**strs;

	strs = malloc(sizeof(char *) * (quot_count(s, set) + 1));
	if (!strs)
		return (NULL);
	i = 0;
	w = 0;
	in_quote = 0;
	open_quote = 0;
	printf("ca rentre boucle\n");
	while (s && s[i])
	{
		if (is_charset(s[i], set) && !in_quote)
			i++;
		else
		{
			start = i;
			while (s[i] && (!is_charset(s[i], set) || in_quote))
			{
				if (i > 0 && (s[i - 1] == '\'' || s[i - 1] == '"') && !in_quote)
				{
					open_quote = s[i - 1];
					in_quote = 1;
					i--;
					start = i;
				}
				else if (in_quote == 1 && s[i] == open_quote && i != start)
				{
					open_quote = 0;
					in_quote = 0;
				}
				i++;
			}
			printf("s = %s, start = %d, i = %d\n", s, start, i - start);
			strs[w] = ft_substr(s, start, i - start);
			w++;
		}
	}
	strs[w] = NULL;
	if (in_quote == 1)
	{
		printf("Error : unclosed quote\n");
		clean_strs(strs, 0, 0);
		return (0);
	}
	return (strs);
}
