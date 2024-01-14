
#include "../minishell.h"

int	set_cmd(t_ccmd *ccmd, char **strs, int *j)
{
	char	*cmd_args;

	cmd_args = NULL;
	ccmd->cmd = ft_strdup(strs[*j]);
	if (!ccmd->cmd)
		return (printf("Minishell: Failed Malloc in set_cmd\n")); //malloc error
	while (strs[*j] && !ft_strchr(strs[*j], '<') && !ft_strchr(strs[*j], '>'))
		cmd_args = join_w_space(cmd_args, strs[(*j)++]);
	if (!cmd_args)
		return (printf("Minishell: Failed Malloc in set_cmd\n")); //malloc error
	ccmd->cmd_arg = ms_split(cmd_args, " ");
	if (!ccmd->cmd_arg)
	{
		printf("Minishell: Failed Malloc in set_cmd\n");
		return (free(cmd_args), 1); //malloc error
	}
	free(cmd_args);
	return (0);
}

int	set_redirs(char **strs, char **in, char **out, int *j)
{
	while (strs[*j] && (!ft_strncmp(strs[*j], ">", ft_strlen(strs[*j])) || !ft_strncmp(strs[*j], ">>", ft_strlen(strs[*j]))))
	{
		if (!strs[*j + 1])
			return (printf("Missing file name after %s\n", strs[*j])); //parse error
		*out = join_w_space(*out, strs[*j]);
		if (!*out)
			return (printf("Minishell: Failed Malloc in set_redirs\n")); //malloc error
		*out = join_w_tab(*out, strs[*j + 1]);
		if (!*out)
			return (printf("Minishell: Failed Malloc in set_redirs\n")); //malloc error
		*j += 2;
	}
	while (strs[*j] && (!ft_strncmp(strs[*j], "<", ft_strlen(strs[*j])) || !ft_strncmp(strs[*j], "<<", ft_strlen(strs[*j]))))
	{
		if (!strs[*j + 1])
			return (printf("Missing file name after %s\n", strs[*j])); //parse error
		*in = join_w_space(*in, strs[*j]);
		if (!*in)
			return (printf("Minishell: Failed Malloc in set_redirs\n")); //malloc error
		*in = join_w_tab(*in, strs[*j + 1]);
		if (!*in)
			return (printf("Minishell: Failed Malloc in set_redirs\n")); //malloc error
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
			return (printf("Minishell: Failed Malloc in set_in_out\n")); //malloc error
		free(*in);
	}
	if (*out)
	{
		ccmd->out = ms_split(*out, "\t");
		if (!ccmd->out)
		{
			if (*in)
			{
				printf("Minishell: Failed Malloc in set_in_out\n");
				return (free(*in), 1); //malloc error
			}
			return (printf("Minishell: Failed Malloc in set_in_out\n")); //malloc error
		}
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

void	init_clean(char **strs, char *in, char *out)
{
	if (strs)
		clean_strs(strs, 0, 0);
	if (in)
		free(in);
	if (out)
		free(out);
}

int	init_ccmd(t_data *d, t_ccmd *ccmd)
{
	int		i;
	char	*in;
	char	*out;
	char	**strs;

	init_zero(d);
	i = -1;
	while (d->cmds[++i])
	{
		if (input_check(d))
			return (printf("Minishell: Incorrect synthax\n"));
		strs = ms_split(d->cmds[i], "\t ");
		if (!strs)
			return (printf("Minishell: Failed Malloc in init_ccmd\n"));
		in = NULL;
		out = NULL;
		if (loop_cmd(ccmd + i, strs, &in, &out))
			return (init_clean(strs, in, out), 1);
		if (set_in_out(ccmd + i, &in, &out))
			return (init_clean(strs, in, out) ,1);
		clean_strs(strs, 0, 0);
	}
	return (0);
}
