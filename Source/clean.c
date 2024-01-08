
#include "../minishell.h"

void	clean_strs(char **strs1, char **strs2, char **strs3)
{
	char	**strs;

	if (strs1)
	{
		strs = strs1;
		while (*strs)
			free(*(strs++));
		free(strs1);
	}
	if (strs2)
	{
		strs = strs2;
		while (*strs)
			free(*(strs++));
		free(strs2);
	}
	if (strs3)
	{
		strs = strs3;
		while (*strs)
			free(*(strs++));
		free(strs3);
	}
}

void	clean_ccmd(t_ccmd *ccmd)
{
	clean_strs(ccmd->cmd_arg, ccmd->in, ccmd->out);
	if (ccmd->cmd)
		free(ccmd->cmd);
	if (ccmd->prev_op)
		free(ccmd->prev_op);
	if (ccmd->next_op)
		free(ccmd->next_op);
}

int	clean_data(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->cmd_count)
	{
		if (d->cmd + i)
			clean_ccmd(d->cmd + i);
		i++;
	}
	if (d->cmd)
		free(d->cmd);
	clean_strs(d->seps, d->cmds, 0);
	return (0);
}