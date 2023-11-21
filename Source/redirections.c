#include "../minishell.h"

int	redir_in(t_data *d, char **env)
{
	d->f1 = open(d->cmd.file_in, O_RDONLY);
	if (d->f1 < 0)
		return (1);
	pipe(d->end);
	dup2(d->f1, 0);
	close(d->f1);
	exec_1(&d->cmd, env);
}
