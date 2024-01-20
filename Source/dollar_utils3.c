
#include "../minishell.h"

size_t	ft_trslen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (i);
	if (!ft_strncmp(s, "$$", 2))
		return (1);
	else
	{
		while (s[i])
			i++;
	}
	return (i);
}

int	dollar_replace2(t_data *d, char **s, int op, int start)
{
	int		i;
	char	*str;
	char	*tmp;

	str = ft_strchr(*s + start, '$');
	while (str != 0 && op-- > 0)
	{
		if (find_match(d, &i, &tmp, str))
			return (1);
		if (tmp)
		{
			str = recreate_str(d, start, s, &tmp);
			if (!str)
				return (free(tmp), 1);
			free(*s);
			*s = ft_strdup(str);
			if (!*s)
				return ((free(str), free(tmp)), 1);
			free(str);
			str = ft_strchr(*s + start + len_varval(d, tmp, 0), '$');
			start += len_varval(d, tmp, 0);
			free(tmp);
		}
	}
	return (0);
}

int	ministrlen(char **strs)
{
	if (!strs)
		return (0);
	if (strs_len(strs) == 0)
		return (ft_strlen(strs[0]));
	return (ft_strlen(strs[0]) + ft_strlen(strs[1]));
}

char	*minijoin(char **strs)
{
	size_t	size;
	char	*str;

	if (!strs)
		return (NULL);
	if (strs_len(strs) == 0)
	{
		str = ft_strdup(strs[0]);
		if (!str)
			return (NULL);
		return (str);
	}
	size = ft_strlen(strs[0]) + ft_strlen(strs[1]);
	str = malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	str[0] = 0;
	ft_strlcat(str, strs[0], size + 1);
	ft_strlcat(str, strs[1], size + 1);
	return (str);
}
