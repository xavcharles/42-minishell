
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
		op--;
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

// int	dollar_replace2(t_data *d, char **s, int op, int start)
// {
// 	int	i;
// 	char	*str;
// 	char	*tmp;

// 	str = ft_strchr(*s + start, '$');
// 	while (str != 0 && op > 0)
// 	{
// 		if (find_match(d, &i, &tmp, str))
// 			return (1);
// 		if (tmp && str[i] && !is_charset(str[i], " \t\"'"))
// 		{
// 			str = recreate_str(d, start, s, &tmp);
// 			if (!str)
// 				return (free(tmp), 1);
// 			free(*s);
// 			*s = ft_strdup(str);
// 			if (!*s)
// 				return ((free(str), free(tmp)), 1);
// 			free(str);
// 			str = ft_strchr(*s + start + len_varval(d, tmp, 0), '$');
// 			start += len_varval(d, tmp, 0);
// 			free(tmp);
// 		}
// 		op--;
// 	}
// 	return (0);
// }

// int	do_dollar_o(t_data *d, t_ccmd *cmd, int i, int *j)
// {
// 	int	start;

// 	start = *j;
// 	printf("start k = %d\n", *j);
// 	while (cmd->out[i][++(*j)] == '$')
// 		;
// 	if (*j - start == 1)
// 		(*j)--;
// 	if (*j != start)
// 	{
// 		if (dollar_replace(d, cmd->out + i, (*j - start) / 2, &start))
// 			return (1);
// 		// *j -= (*j - start) % 2;
// 	}
// 	else
// 		if (dollar_replace(d, cmd->out + i, 1, &start))
// 			return (1);
// 	// if (d->cmd[i].cmd_arg[i][*j] != '$' || d->cmd[i].cmd_arg[i][*j + 1] != 0)
// 	*j = start;
// 	printf("end k = %d\n", *j);
// 	return (0);
// }

// int	dollar_outloop(t_data *d, t_ccmd *cmd, int i, int *j)
// {
// 	char	*out;

// 	out = cmd->out[i];
// 	if (out[*j] == '$')
// 	{
// 		if (do_dollar(d, i, j, k))
// 			return (1);
// 	}
// 	else if (out[*j] == '\'')
// 	{
// 		if (do_squote(d, i, j, k))
// 			return (1);
// 	}
// 	else if (out[*j] == '"')
// 	{
// 		if (do_dquote(d, i, j, k))
// 			return (1);
// 	}
// 	return (0);
// }

int	dollar_inout(t_data *d, t_ccmd *cmd)
{
	int	i;
	int	j;

	if (cmd->out)
	{
		i = -1;
		while (cmd->out[++i])
		{
			j = -1;
			while (cmd->out[i][++j])
			{
				if (dollar_loop(d, cmd, cmd->out + i, &j))
					return (1);
			}
		}
	}
	return (0);
}
