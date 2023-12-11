
#include "../minishell.h"

int		is_charset(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i++])
			return (1);
	}
	return (0);
}

int	cmd_count(char const *s, char *set)
{
	int	i;
	int	w;

	i = 0;
	w = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (is_charset(s[i], set))
			i++;
		else
		{
			while (s[i] && !is_charset(s[i], set))
				i++;
			w++;
		}
	}
	return (w);
}

int	sep_count(char const *s, char *set)
{
	int	i;
	int	w;

	i = 0;
	w = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (!is_charset(s[i], set))
			i++;
		else
		{
			while (s[i] && is_charset(s[i], set))
				i++;
			w++;
		}
	}
	return (w);
}

char	**ms_split(char *s, char *set)
{
	int		w;
	int		i;
	int		start;
	char	**strs;

	strs = malloc(sizeof(char *) * (cmd_count(s, set) + 1));
	if (!strs)
		return (NULL);
	i = 0;
	w = 0;
	while (s && s[i])
	{
		if (is_charset(s[i], set))
			i++;
		else
		{
			start = i;
			while (s[i] && !is_charset(s[i], set))
				i++;
			strs[w] = ft_substr(s, start, i - start);
			w++;
		}
	}
	strs[w] = NULL;
	return (strs);
}

char	**rev_ms_split(char *s, char *set)
{
	int		w;
	int		i;
	int		start;
	char	**strs;

	strs = malloc(sizeof(char *) * (sep_count(s, set) + 1));
	if (!strs)
		return (NULL);
	i = 0;
	w = 0;
	while (s && s[i])
	{
		if (!is_charset(s[i], set))
			i++;
		else
		{
			start = i;
			while (s[i] && is_charset(s[i], set))
				i++;
			strs[w] = ft_substr(s, start, i - start);
			w++;
		}
	}
	strs[w] = NULL;
	return (strs);
}
