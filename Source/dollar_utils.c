
#include "../minishell.h"

int	find_match(t_data *d, int *i, char **tmp, char *str)
{
	*tmp = NULL;
	*i = 0;
	while (str[++(*i)] && !is_charset(str[*i], " $\t\"'"))
	{
		if (*tmp)
			free(*tmp);
		if (*i == 1 && str[*i] == '?')
			*tmp = ft_strdup("?");
		if (!*tmp && *i == 1 && str[*i] == '?')
			return (1);
		if (*i == 1 && str[*i] == '?')
			break ;
		*tmp = ft_substr(str + 1, 0, *i);
		if (!*tmp)
			return (1);
		if (find_var(d->env, *tmp))
			break ;
	}
	if ((*i) > 0 && str[(*i)] == '$' && str[(*i) - 1] == '$')
	{
		*tmp = ft_substr(str, 0, *(i) + 1);
		if (!*tmp)
			return (1);
	}
	return (0);
}

char	*recreate_str(t_data *d, int start, char **s, char **tmp)
{
	char	*val;
	char	*str;
	int		len;

	len = ft_strlen(*s) - ft_strlen(*tmp) + ven_larlav(d, *tmp);
	val = env_varval(d, *tmp);
	if (!val && len_varval(d, *tmp, 0) != 0)
		return (free(*tmp), NULL);
	str = ft_calloc(len, sizeof(char *));
	if (!str)
	{
		if (val)
			free(val);
		return (free(*tmp), NULL);
	}
	len = ft_strlen(*s) - ft_strlen(ft_strchr(*s + start, '$'));
	ft_strlcat(str, *s, len + 1);
	len += len_varval(d, *tmp, 0);
	if (val)
		ft_strlcat(str, val, len + 1);
	len += ft_strlen(ft_strchr(*s + start, '$')) - ft_trslen(*tmp) - 1;
	ft_strlcat(str, ft_strchr(*s + start, '$') + ft_trslen(*tmp) + 1, len + 1);
	if (val)
		free(val);
	return (str);
}

int	dollar_replace(t_data *d, char **s, int op, int *start)
{
	int		i;
	char	*str;
	char	*tmp;

	str = ft_strchr(*s + *start, '$');
	while (str != 0 && op-- > 0)
	{
		if (find_match(d, &i, &tmp, str))
			return (1);
		if (tmp)
		{
			str = recreate_str(d, *start, s, &tmp);
			if (!str)
				return (free(tmp), 1);
			free(*s);
			*s = ft_strdup(str);
			if (!*s)
				return ((free(str), free(tmp)), 1);
			free(str);
			str = ft_strchr(*s + *start + len_varval(d, tmp, 0), '$');
			*start += len_varval(d, tmp, op) - 1;
			free(tmp);
		}
	}
	return (0);
}

int	s_quote1(char **tmp, char *arg, int *k)
{
	int		start;
	char	**strs;
	char	*str;

	start = *k;
	while (arg[++(*k)] != '\'')
		;
	str = ft_substr(arg, start, *k - start);
	if (!str)
		return (1);
	strs = ft_split(str, '\'');
	if (!strs)
		return (free(str), 1);
	free(str);
	str = minijoin(strs);
	if (!str)
		return (clean_strs(strs, 0, 0), 1);
	clean_strs(strs, 0, 0);
	*tmp = ft_substr(arg, 0, start);
	if (!(*tmp))
		return (free(str), 1);
	*tmp = gnl_strjoin(*tmp, str);
	if (!(*tmp))
		return (free(str), 1);
	return (free(str), 0);
}

int	d_quote1(t_data *d, char ***strs, char *arg, int *k)
{
	char	*str;

	while (arg[++(*k)] != '"')
		;
	str = ft_substr(arg, 0, *k);
	if (!str)
		return (1);
	*strs = ft_split(str, '"');
	if (!*strs)
		return (free(str), 1);
	free(str);
	if (strs_len(*strs) == 2)
	{
		if (dollar_replace2(d, *strs + 1, ft_strlen(*(*strs + 1)), 0))
			return (clean_strs(*strs, 0, 0), 1);
	}
	else
	{
		if (dollar_replace2(d, *strs, ft_strlen(**strs), 0))
			return (clean_strs(*strs, 0, 0), 1);
	}
	return (0);
}
