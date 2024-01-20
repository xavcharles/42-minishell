
#include "../minishell.h"

int	add_tmp(char *tmp, char **cmd_arg, char **in, char **out)
{
	if (!tmp)
		return (1);
	if (*in && (*in)[ft_strlen(*in) - 1] == '<')
	{
		*in = join_w_tab(*in, tmp);
		if (!*in)
			return (free(tmp), 1);
	}
	else if (*out && (*out)[ft_strlen(*out) - 1] == '>')
	{
		*out = join_w_tab(*out, tmp);
		if (!*out)
			return (free(tmp), 1);
	}
	else
	{	
		*cmd_arg = join_w_space(*cmd_arg, tmp);
		if (!*cmd_arg)
			return (free(tmp), 1);
	}
	free(tmp);
	return (0);
}

int fill_argsinout(char *str, char **cmd_arg, char **in, char **out)
{
	int	i;
	int	inquote;
	char	start_q;
	char	*tmp;

	i = 0;
	inquote = 0;
	while (str[i] && (!is_charset(str[i], "<>") || inquote == 1))
	{
		if (is_charset(str[i], "'\"") && inquote == 0)
		{
			inquote = 1;
			start_q = str[i];
		}
		else if (inquote == 1 && str[i] == start_q)
		{
			inquote = 0;
			start_q = 0;
		}
		i++;
	}
	tmp = ft_substr(str, 0, i);
	if (add_tmp(tmp, cmd_arg, in, out))
		return (-1);
	return (i);
}

int	loop_2(char *str, char **cmd_arg, char **in, char **out)
{
	int	i;
	int	d;

	i = 0;
	while (str[i])
	{
		if (!is_charset(str[i], "<>"))
		{
			d = i;
			i += fill_argsinout(str + i, cmd_arg, in, out);
			if (i < d)
				return (1);
		}
		else
			if (fill_justthesign(str, in, out, &i))
				return (1);
	}
	return (0);
}
