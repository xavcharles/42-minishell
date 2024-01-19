
#include "../minishell.h"

int	do_dquote(t_data *d, t_ccmd *ccmd, char **rep, int *k)
{
	char	*arg;
	char	**strs;
	char	*str;

	arg = *rep;
	if (d_quote1(d, &strs, arg, k))
		return (clean_strs(strs, 0, 0), 1);
	str = minijoin(strs);
	if (!str)
		return (clean_strs(strs, 0, 0), 1);
	*rep = gnl_strjoin(str, arg + *k + 1);
	if (!*rep)
		return (free(arg), 1);
	free(arg);
	*k = ministrlen(strs) - 1;
	clean_strs(strs, 0, 0);
	if (ccmd->cmd_arg == rep)
	{
		free(ccmd->cmd);
		ccmd->cmd = ft_strdup(ccmd->cmd_arg[0]);
		if (!ccmd->cmd)
			return (1);
	}
	(void) d;
	return (0);
}

int	do_squote(t_data *d, t_ccmd *ccmd, char **rep, int *k)
{
	char	*tmp;
	char	*arg;

	arg = *rep;
	if (s_quote1(&tmp, arg, k))
		return (1);
	*rep = gnl_strjoin(tmp, arg + *k + 1);
	if (!*rep)
		return (free(arg), 1);
	free(arg);
	if (ccmd->cmd_arg == rep)
	{
		free(ccmd->cmd);
		ccmd->cmd = ft_strdup(ccmd->cmd_arg[0]);
		if (!ccmd->cmd)
			return (1);
	}
	*k -= 2;
	(void) d;
	return (0);
}

int	do_dollar(t_data *d, t_ccmd *ccmd, char **rep, int *k)
{
	int	start;

	start = *k;
	while ((*rep)[++(*k)] == '$')
		;
	if (*k - start == 1)
		(*k)--;
	if (*k != start)
	{
		if (dollar_replace(d, rep, (*k - start) / 2, &start))
			return (1);
		// *k -= (*k - start) % 2;
	}
	else
		if (dollar_replace(d, rep, 1, &start))
			return (1);
	if (ccmd->cmd_arg[0] == *rep)
	{
		ccmd->cmd = ft_strdup(ccmd->cmd_arg[0]);
		if (!ccmd->cmd)
			return (1);
	}
	*k = start;
	return (0);
}

int	dollar_loop(t_data *d, t_ccmd *ccmd, char **rep, int *k)
{
	char	*arg;
	char	*old;

	arg = *rep;
	if (arg[*k] == '$')
	{
		old = ccmd->cmd;
		if (do_dollar(d, ccmd, rep, k))
			return (1);
		if (old != ccmd->cmd)
			free(old);
	}
	else if (arg[*k] == '\'')
	{
		if (do_squote(d, ccmd, rep, k))
			return (1);
	}
	else if (arg[*k] == '"')
	{
		if (do_dquote(d, ccmd, rep, k))
			return (1);
	}
	return (0);
}

int	dollar_search(t_data *d)
{
	int	i;
	int	j;
	int	k;

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
					if (dollar_loop(d, d->cmd + i, d->cmd[i].cmd_arg + j, &k))
						return (1);
				}
			}	
		}
		if (d->cmd[i].in || d->cmd[i].out)
			if (dollar_inout(d, d->cmd + i))
				return (1);
	}
	return (0);
}

// int	do_dquote(t_data *d, int i, int j, int *k)
// {
// 	char	*arg;
// 	char	**strs;
// 	char	*str;

// 	arg = d->cmd[i].cmd_arg[j];
// 	if (d_quote1(d, &strs, arg, k))
// 		return (clean_strs(strs, 0, 0), 1);
// 	str = ft_strjoin(strs[0], strs[1]);
// 	if (!str)
// 		return (clean_strs(strs, 0, 0), 1);
// 	d->cmd[i].cmd_arg[j] = gnl_strjoin(str, arg + *k + 1);
// 	if (!d->cmd[i].cmd_arg[j])
// 		return (free(arg), 1);
// 	free(arg);
// 	*k = ft_strlen(strs[0]) + ft_strlen(strs[1]) - 1;
// 	clean_strs(strs, 0, 0);
// 	if (j == 0)
// 	{
// 		free(d->cmd[i].cmd);
// 		d->cmd[i].cmd = ft_strdup(d->cmd[i].cmd_arg[0]);
// 		if (!d->cmd[i].cmd)
// 			return (1);
// 	}
// 	return (0);
// }

// int	do_squote(t_data *d, int i, int j, int *k)
// {
// 	char	*tmp;
// 	char	*arg;

// 	arg = d->cmd[i].cmd_arg[j];
// 	if (s_quote1(&tmp, arg, k))
// 		return (1);
// 	d->cmd[i].cmd_arg[j] = gnl_strjoin(tmp, arg + *k + 1);
// 	if (!d->cmd[i].cmd_arg[j])
// 		return (free(arg), 1);
// 	free(arg);
// 	if (j == 0)
// 	{
// 		free(d->cmd[i].cmd);
// 		d->cmd[i].cmd = ft_strdup(d->cmd[i].cmd_arg[0]);
// 		if (!d->cmd[i].cmd)
// 			return (1);
// 	}
// 	*k -= 3;
// 	return (0);
// }

// int	do_dollar(t_data *d, int i, int j, int *k)
// {
// 	int	start;

// 	start = *k;
// 	while (d->cmd[i].cmd_arg[j][++(*k)] == '$')
// 		;
// 	if (*k - start == 1)
// 		(*k)--;
// 	if (*k != start)
// 	{
// 		if (dollar_replace(d, d->cmd[i].cmd_arg + j, (*k - start) / 2, &start))
// 			return (1);
// 		// *k -= (*k - start) % 2;
// 	}
// 	else
// 		if (dollar_replace(d, d->cmd[i].cmd_arg + j, 1, &start))
// 			return (1);
// 	if (j == 0)
// 	{
// 		d->cmd[i].cmd = ft_strdup(d->cmd[i].cmd_arg[0]);
// 		if (!d->cmd[i].cmd)
// 			return (1);
// 	}
// 	*k = start;
// 	printf("end k = %d\n", *k);
// 	return (0);
// }

// int	dollar_loop(t_data *d, int i, int j, int *k)
// {
// 	char	*arg;
// 	char	*old;

// 	arg = d->cmd[i].cmd_arg[j];
// 	if (arg[*k] == '$')
// 	{
// 		old = d->cmd[i].cmd;
// 		if (do_dollar(d, i, j, k))
// 			return (1);
// 		if (old != d->cmd[i].cmd)
// 			free(old);
// 	}
// 	else if (arg[*k] == '\'')
// 	{
// 		if (do_squote(d, i, j, k))
// 			return (1);
// 	}
// 	else if (arg[*k] == '"')
// 	{
// 		if (do_dquote(d, i, j, k))
// 			return (1);
// 	}
// 	return (0);
// }

// int	dollar_search(t_data *d)
// {
// 	int	i;
// 	int	j;
// 	int	k;

// 	i = -1;
// 	while (++i < d->cmd_count)
// 	{
// 		if (d->cmd[i].cmd)
// 		{
// 			j = -1;
// 			while (d->cmd[i].cmd_arg[++j])
// 			{
// 				k = -1;
// 				while (d->cmd[i].cmd_arg[j][++k])
// 				{
// 					if (dollar_loop(d, i, j, &k))
// 						return (1);
// 				}
// 			}	
// 		}
// 		// if (d->cmd[i].in || d->cmd[i].out)
// 		// 	if (dollar_inout(d, d->cmd + i))
// 		// 		return (1);
// 	}
// 	return (0);
// }
