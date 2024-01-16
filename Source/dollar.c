
#include "../minishell.h"

char	*env_varval(t_data *d, char *str)
{
	int	i;
	int	len;
	char	*tmp;

	i = 0;
	while (d->env[i])
	{
		if (!ft_strncmp(d->env[i], str, ft_strlen(str)))
		{
			if (!ft_strchr(d->env[i], '='))
				return (NULL);
			else
			{
				len = ft_strlen(ft_strchr(d->env[i], '=') - 1);
				tmp = ft_substr(d->env[i], ft_strlen(str) + 1, len);
				if (!tmp)
					return (NULL);
				return (tmp);
			}
		}
		i++;
	}
	return (NULL);
}

int	len_varval(t_data *d, char *str)
{
	int	i;

	i = 0;
	while (d->env[i])
	{
		if (!ft_strncmp(d->env[i], str, ft_strlen(str)))
		{
			if (!ft_strchr(d->env[i], '='))
				return (0);
			else
				return (ft_strlen(ft_strchr(d->env[i], '=') - 1));
		}
		i++;
	}
	return (0);
}

int	dollar_replace(t_data *d, char **s, int op, int start)
{
	int	i;
	int	len;
	char	*str;
	char	*tmp;
	char	*val;

	str = ft_strchr(*s + start, '$');
	while (str != 0 && op > 0)
	{
		tmp = NULL;
		i = 0;
		while (str[++i] && !is_charset(str[i], " \t\"'"))
		{
			printf("str[%d] = %c\n", i, str[i]);
			if (tmp)
				free(tmp);
			tmp = ft_substr(str + 1, 0, i);
			if (!tmp)
				return (1);
			printf("i = %d, tmp = %s\n", i, tmp);
			if (find_var(d->env, tmp))
				break ;
			printf("test1\n");
		}
		if (i > 1)
		{
			len = ft_strlen(*s) - ft_strlen(tmp) + len_varval(d, tmp);
			val = env_varval(d, tmp);
			if (!val && len_varval(d, tmp) != 0)
				return (free(tmp), 1);
			printf("len = %d\n %zu, %zu, %d\n", len, ft_strlen(*s), ft_strlen(tmp), len_varval(d, tmp));
			str = ft_calloc(len, sizeof(char*));
			if (!str)
			{
				if (val)
					free(val);
				return (free(tmp), 1);
			}
			i = ft_strlen(*s) - ft_strlen(ft_strchr(*s + start, '$'));
			ft_strlcat(str, *s, i + 1);
			i += len_varval(d, tmp);
			if (val)
				ft_strlcat(str, val, i + 1);
			i += ft_strlen(ft_strchr(*s + start, '$')) - ft_strlen(tmp) - 1;
			ft_strlcat(str, ft_strchr(*s + start, '$') + ft_strlen(tmp) + 1, i + 1);
			if (val)
				free(val);
			free(tmp);
			free(*s);
			*s = ft_strdup(str);
			if (!*s)
				return (free(str), 1);
			free(str);
			str = ft_strchr(*s, '$');
			printf("s = %s, str= %s\n", *s, str);
		}
		op--;
	}
	return (0);
}

int	repl_cmd_squote(t_data *d, int i)
{
	char	*tmp;

	tmp = ft_strtrim(d->cmd[i].cmd, "'");
	if (!tmp)
		return (1);
	free(d->cmd[i].cmd_arg[0]);
	d->cmd[i].cmd_arg[0] = ft_strdup(tmp);
	if (!d->cmd[i].cmd_arg[0])
		return (free(tmp), 1);
	free(d->cmd[i].cmd);
	d->cmd[i].cmd = ft_strdup(tmp);
	if (!d->cmd[i].cmd)
		return (free(tmp), 1);
	free(tmp);
	return (0);
}

// int	repl_cmd_dquote(t_data *d, int i)
// {
// 	char	*tmp;

// 	tmp = ft_strtrim(d->cmd[i].cmd, "\"");
// 	if (!tmp)
// 		return (1);
// 	if (ft_strchr(d->cmd[i].cmd, '$'))
// 	{
// 		if (dollar_replace(d, &tmp))
// 			return (1);
// 	}
// 	free(d->cmd[i].cmd_arg[0]);
// 	d->cmd[i].cmd_arg[0] = ft_strdup(tmp);
// 	if (!d->cmd[i].cmd_arg[0])
// 		return (free(tmp), 1);
// 	free(d->cmd[i].cmd);
// 	d->cmd[i].cmd = ft_strdup(tmp);
// 	if (!d->cmd[i].cmd)
// 		return (free(tmp), 1);
// 	free(tmp);
// 	return (0);
// }

// int	repl_cmd_noquote(t_data *d, int i)
// {
// 	char	*tmp;

// 	tmp = ft_str;
// 	if (!tmp)
// 		return (1);
// 	if (ft_strchr(d->cmd[i].cmd, '$'))
// 	{
// 		if (dollar_replace(d, &tmp))
// 			return (1);
// 	}
// 	free(d->cmd[i].cmd_arg[0]);
// 	d->cmd[i].cmd_arg[0] = ft_strdup(tmp);
// 	if (!d->cmd[i].cmd_arg[0])
// 		return (free(tmp), 1);
// 	free(d->cmd[i].cmd);
// 	d->cmd[i].cmd = ft_strdup(tmp);
// 	if (!d->cmd[i].cmd)
// 		return (free(tmp), 1);
// 	free(tmp);
// 	return (0);
// }

int	repl_arg_squote(t_data *d, int i, int j)
{
	char	*tmp;

	tmp = ft_strtrim(d->cmd[i].cmd_arg[j], "'");
	if (!tmp)
		return (1);
	free(d->cmd[i].cmd_arg[j]);
	d->cmd[i].cmd_arg[j] = ft_strdup(tmp);
	free(tmp);
	if (!d->cmd[i].cmd_arg[j])
		return (1);
	return (0);
}

// int	repl_arg_dquote(t_data *d, int i, int j)
// {
// 	char	*tmp;

// 	tmp = ft_strtrim(d->cmd[i].cmd_arg[j], "\"");
// 	if (!tmp)
// 		return (1);
// 	if (ft_strchr(d->cmd[i].cmd_arg[j], '$'))
// 	{
// 		if (dollar_replace(d, &tmp))
// 			return (1);
// 	}
// 	free(d->cmd[i].cmd_arg[j]);
// 	d->cmd[i].cmd_arg[j] = ft_strdup(tmp);
// 	free(tmp);
// 	if (!d->cmd[i].cmd_arg[j])
// 		return (1);
// 	return (0);
// }

// int	repl_args(t_data *d, int i)
// {
// 	int		j;

// 	j = 0;
// 	while (d->cmd[i].cmd_arg[++j])
// 	{
// 		if (d->cmd[i].cmd_arg[j][0] == '"')
// 		{
// 			if (repl_arg_dquote(d, i, j))
// 				return (1);
// 		}
// 		else if (d->cmd[i].cmd_arg[j][0] == '\'')
// 		{
// 			if (repl_arg_squote(d, i, j))
// 				return (1);
// 		}
// 	}
// 	return (0);
// }

// int	dollar_search(t_data *d)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < d->cmd_count)
// 	{
// 		if (d->cmd[i].cmd)
// 		{
// 			if (d->cmd[i].cmd[0] == '"')
// 			{
// 				if (repl_cmd_dquote(d, i))
// 					return (1);
// 			}
// 			else if (d->cmd[i].cmd[0] == '\'')
// 			{
// 				if (repl_cmd_squote(d, i))
// 					return (1);
// 			}
// 			if (repl_args(d, i))
// 				return (0);
// 		}
// 	}
// 	return (0);
// }

char	*ft_unsplit(char **strs)
{
	int		i;
	int		len;
	char	*str;

	i = -1;
	len = 0;
	while (strs[++i])
		len += ft_strlen(strs[i]);
	str = malloc(sizeof(char *) * (len + 1));
	if (!str)
		return (NULL);
	i = -1;
	str = NULL;
	while (strs[++i])
	{
		str = gnl_strjoin(str, strs[i]);
		if (!str)
			return (free(str), NULL);
	}
	return (str); 
}

int	dollar_search(t_data *d)
{
	int	i;
	int	j;
	int	k;
	int	start;
	char	*arg;
	char	*str;
	char	*tmp;
	char	**strs;

	i = -1;
	while (++i < d->cmd_count)
	{
		if (d->cmd[i].cmd)
		{
			j = -1;
			while (d->cmd[i].cmd_arg[++j])
			{
				k = -1;
				while (d->cmd[i].cmd_arg[j][++k])
				{
					printf("d-arg = %s\n", d->cmd[i].cmd_arg[j]);
					arg = d->cmd[i].cmd_arg[j];
					if (arg[k] == '$')
					{
						printf("if, k = %d, arg[k] = %c\n", k, arg[k]);
						if (dollar_replace(d, d->cmd[i].cmd_arg + j, 1, k))
							return (1);
						printf("test2\n");
						if (j == 0)
						{
							free(d->cmd[i].cmd);
							d->cmd[i].cmd = ft_strdup(d->cmd[i].cmd_arg[0]);
							if (!d->cmd[i].cmd)
								return (1);
						}
						k--;
					}
					else if (arg[k] == '\'')
					{
						printf("else if, k = %d, arg[k] = %c\n", k, arg [k]);
						start = k;
						while (arg[++k] != '\'')
							;
						str = ft_substr(arg, start, k - start);
						if (!str)
							return (1);
						strs = ft_split(str, '\'');
						if (!strs)
							return (free(str), 1);
						free(str);
						str = ft_strjoin(strs[0], strs[1]);
						if (!str)
							return (clean_strs(strs, 0, 0), 1);
						clean_strs(strs, 0, 0);
						tmp = ft_substr(arg, 0, start);
						if (!tmp)
							return (free(str), 1);
						tmp = gnl_strjoin(tmp, str);
						free(str);
						d->cmd[i].cmd_arg[j] = gnl_strjoin(tmp, arg + k + 1);
						free(arg);
						k -= 3;
						if (j == 0)
						{
							free(d->cmd[i].cmd);
							d->cmd[i].cmd = ft_strdup(d->cmd[i].cmd_arg[0]);
							if (!d->cmd[i].cmd)
								return (1);
						}
						printf("else if :md-arg = %s\n", d->cmd[i].cmd_arg[j]);
					}
					else if (arg[k] == '"')
					{
						printf("else if dquote, k = %d, arg[k] = %c\n", k, arg [k]);
						while (arg[++k] != '"')
							;
						str = ft_substr(arg, 0, k);
						if (!str)
							return (1);
						strs = ft_split(str, '"');
						if (!strs)
							return (free(str), 1);
						free(str);
						if (strs_len(strs) == 2)
						{
							if (dollar_replace(d, &strs[1], ft_strlen(strs[1]), 0))
								return (clean_strs(strs, 0, 0), 1);
						}
						else
						{
							if (dollar_replace(d, &strs[0], ft_strlen(strs[0]), 0))
								return (clean_strs(strs, 0, 0), 1);
						}
						str = ft_strjoin(strs[0], strs[1]);
						if (!str)
							return (clean_strs(strs, 0, 0), 1);
						d->cmd[i].cmd_arg[j] = gnl_strjoin(str, arg + k + 1);
						free(arg);
						k = ft_strlen(strs[0]) + ft_strlen(strs[1]) - 1;
						printf("strs[0] = %s, strs[1] = %s\n", strs[0], strs[1]);
						clean_strs(strs, 0, 0);
						if (j == 0)
						{
							free(d->cmd[i].cmd);
							d->cmd[i].cmd = ft_strdup(d->cmd[i].cmd_arg[0]);
							if (!d->cmd[i].cmd)
								return (1);
						}
					}
				}
			}
		}
	}
	return (0);
}
