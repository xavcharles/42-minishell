
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
		// if ((s[i] == '\'' || s[i] == '"') && !in_quote)
		// {
		// 	open_quote = s[i];
		// 	in_quote = 1;
		// 	// i++;
		// }
		if (is_charset(s[i], set) && !in_quote)
			i++;
		else
		{
			while (s[i] && (!is_charset(s[i], set) || in_quote))
			{
				if ((s[i] == '\'' || s[i] == '"') && !in_quote)
				{
					open_quote = s[i];
					in_quote = 1;
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

int	sep_count(char const *s, char *set)
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
		if (s[i] && (!is_charset(s[i], set) || in_quote))
		{
			if ((s[i] == '\'' || s[i] == '"') && !in_quote)
			{
				open_quote = s[i];
				in_quote = 1;
			}
			else if (s[i] == open_quote)
			{
				open_quote = 0;
				in_quote = 0;
			}
			i++;
		}
		else
		{
			while (s[i] && is_charset(s[i], set) && !in_quote)
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
	int		in_quote;
	char	open_quote;
	char	**strs;

	strs = malloc(sizeof(char *) * (cmd_count(s, set) + 1));
	if (!strs)
		return (NULL);
	i = 0;
	w = 0;
	in_quote = 0;
	open_quote = 0;
	while (s && s[i])
	{
		// if ((s[i] == '\'' || s[i] == '"') && !in_quote)
		// {
		// 	open_quote = s[i];
		// 	in_quote = 1;
		// 	// i++;
		// }
		if (is_charset(s[i], set) && !in_quote)
			i++;
		else
		{
			start = i;
			while (s[i] && (!is_charset(s[i], set) || in_quote))
			{
				if ((s[i] == '\'' || s[i] == '"') && !in_quote)
				{
					open_quote = s[i];
					in_quote = 1;
				}
				else if (in_quote == 1 && s[i] == open_quote && i != start)
				{
					open_quote = 0;
					in_quote = 0;
				}
				i++;
			}
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

char	**rev_ms_split(char *s, char *set)
{
	int		w;
	int		i;
	int		in_quote;
	int		start;
	char	open_quote;
	char	**strs;

	strs = malloc(sizeof(char *) * (sep_count(s, set) + 1));
	if (!strs)
		return (NULL);
	i = 0;
	w = 0;
	in_quote = 0;
	open_quote = 0;
	while (s && s[i])
	{
		// if ((s[i] == '\'' || s[i] == '"') && !in_quote)
		// {
		// 	open_quote = s[i];
		// 	in_quote = 1;
		// 	// i++;
		// }
		if (s[i] && (!is_charset(s[i], set) || in_quote))
		{
			if ((s[i] == '\'' || s[i] == '"') && !in_quote)
			{
				open_quote = s[i];
				in_quote = 1;
			}
			else if (s[i] == open_quote)
			{
				open_quote = 0;
				in_quote = 0;
			}
			i++;
		}
		else
		{
			start = i;
			while (s[i] && is_charset(s[i], set) && !in_quote)
				i++;
			strs[w] = ft_substr(s, start, i - start);
			w++;
		}
	}
	strs[w] = NULL;
	return (strs);
}
