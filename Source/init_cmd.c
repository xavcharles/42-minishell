
#include "../minishell.h"

int	set_cmd(t_ccmd *ccmd, char **strs, int *j)
{
	char	*cmd_args;

	cmd_args = NULL;
	ccmd->cmd = ft_strdup(strs[*j]);
	if (!ccmd->cmd)
		return (1); //malloc error
	while (strs[*j] && !ft_strchr(strs[*j], '<') && !ft_strchr(strs[*j], '>'))
		cmd_args = join_w_space(cmd_args, strs[(*j)++]);
	if (!cmd_args)
		return (1); //malloc error
	ccmd->cmd_arg = ms_split(cmd_args, " ");
	if (!ccmd->cmd_arg)
		return (free(cmd_args), 1); //malloc error
	free(cmd_args);
	return (0);
}

int	set_redirs(char **strs, char **in, char **out, int *j)
{
	while (strs[*j] && (!ft_strncmp(strs[*j], ">", ft_strlen(strs[*j])) || !ft_strncmp(strs[*j], ">>", ft_strlen(strs[*j]))))
	{
		if (!strs[*j + 1])
			return (1); //parse error
		*out = join_w_space(*out, strs[*j]);
		if (!*out)
			return (1); //malloc error
		*out = join_w_tab(*out, strs[*j + 1]);
		if (!*out)
			return (1); //malloc error
		*j += 2;
	}
	while (strs[*j] && (!ft_strncmp(strs[*j], "<", ft_strlen(strs[*j])) || !ft_strncmp(strs[*j], "<<", ft_strlen(strs[*j]))))
	{
		if (!strs[*j + 1])
			return (1); //parse error
		*in = join_w_space(*in, strs[*j]);
		if (!*in)
			return (1); //malloc error
		*in = join_w_tab(*in, strs[*j + 1]);
		if (!*in)
			return (1); //malloc error
		*j += 2;
	}
	return (0);
}

int	set_in_out(t_ccmd *ccmd, char **in, char **out)
{
	if (*in)
	{
		ccmd->in = ms_split(*in, "\t");
		if (!ccmd->in)
			return (1); //malloc error
		free(*in);
	}
	if (*out)
	{
		ccmd->out = ms_split(*out, "\t");
		if (!ccmd->out)
			return (1); //malloc error
		free(*out);
	}
	return (0);
}

int	loop_cmd(t_ccmd *ccmd, char **strs, char **in, char **out)
{
	int		j;

	j = 0;
	while (strs[j])
	{
		if (!ft_strchr(strs[j], '<') && !ft_strchr(strs[j], '>'))
		{
			if (set_cmd(ccmd, strs, &j))
				return (1);
		}
		else
		{
			if (set_redirs(strs, in, out, &j))
				return (1);
		}
	}
	return (0);
}

int	init_ccmd(t_data *d, t_ccmd *ccmd)
{
	int		i;
	char	*in;
	char	*out;
	char	**strs;

	init_zero(d);
	i = 0;
	while (d->cmds[i])
	{
		if (input_check(d))
			return (1);
		strs = ms_split(d->cmds[i], "\t ");
		if (!strs)
			return (1);
		in = NULL;
		out = NULL;
		if (loop_cmd(ccmd + i, strs, &in, &out))
			return (clean_strs(strs, 0, 0), 1);
		if (set_in_out(ccmd + i, &in, &out))
			return (clean_strs(strs, 0, 0) ,1);
		clean_strs(strs, 0, 0);
		i++;
	}
	return (0);
}
