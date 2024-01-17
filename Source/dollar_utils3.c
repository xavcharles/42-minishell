
#include "../minishell.h"

int	dollar_replace2(t_data *d, char **s, int op, int start)
{
	int	i;
	char	*str;
	char	*tmp;

	str = ft_strchr(*s + start, '$');
	while (str != 0 && op > 0)
	{
		if (find_match(d, &i, &tmp, str))
			return (1);
		if (tmp && str[i] && !is_charset(str[i], " \t\"'"))
		{
			str = recreate_str(d, start, s, &tmp);
			if (!str)
				return (free(tmp), 1);
			free(*s);
			*s = ft_strdup(str);
			if (!*s)
				return ((free(str), free(tmp)), 1);
			free(str);
			str = ft_strchr(*s + start + len_varval(d, tmp), '$');
			start += len_varval(d, tmp);
			free(tmp);
		}
		op--;
	}
	return (0);
}