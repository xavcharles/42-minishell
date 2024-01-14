
#include "../minishell.h"

int	set_op_pipe(int j, t_ccmd *ccmd, char *input)
{
	if (!ft_strncmp(input + j, "||", 2))
	{
		ccmd->next_op = ft_strdup("||");
		if (!ccmd->next_op)
			return (1); //malloc error
	}
	else if (!ft_strncmp(input + j, "|", 1))
	{
		ccmd->next_op = ft_strdup("|");
		if (!ccmd->next_op)
			return (1); //malloc error
	}
	return (0);
}

int	set_op_and(int j, t_ccmd *ccmd, char *input)
{
	if (!ft_strncmp(input + j, "&&", 2))
	{
		ccmd->next_op = ft_strdup("&&");
		if (!ccmd->next_op)
			return (1); //malloc error
	}
	else if (!ft_strncmp(input + j, "&", 1))
	{
		ccmd->next_op = ft_strdup("&");
		if (!ccmd->next_op)
			return (1); //malloc error
	}
	return (0);
}

int	set_prev_op(int j, t_ccmd *ccmd, char *input)
{
	if (!ft_strncmp(input + j, "&&", 2))
	{
		ccmd->prev_op = ft_strdup("&&");
		if (!ccmd->prev_op)
			return (1); //malloc error
	}
	else if (!ft_strncmp(input + j, "||", 2))
	{
		ccmd->prev_op = ft_strdup("||");
		if (!ccmd->prev_op)
			return (1); //malloc error
	}
	else if (!ft_strncmp(input + j, "|", 1))
	{
		ccmd->prev_op = ft_strdup("|");
		if (!ccmd->prev_op)
			return (1); //malloc error
	}
	else if (!ft_strncmp(input + j, "&", 1))
	{
		ccmd->prev_op = ft_strdup("&");
		if (!ccmd->prev_op)
			return (1); //malloc error
	}
	return (0);
}

int	set_next_op(t_data *d, char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	d->cmd[i].prev_op = NULL;
	while (d->cmds[i + 1])
	{
		d->cmd[i].next_op = NULL;
		if (j > 0)
			if (set_prev_op(j, d->cmd + i, input))
				return (1);
		j += ft_strlen(d->cmds[i]) + ft_strlen(d->cmd[i].prev_op);
		if (set_op_pipe(j, d->cmd + i, input))
			return(1); //maloc error
		if (set_op_and(j, d->cmd + i, input))
			return(1); //maloc error
		i++;
	}
	if (i > 0)
		if (set_prev_op(j, d->cmd + i, input))
			return (1);
	d->cmd[i].next_op = NULL;
	return (0);
}
