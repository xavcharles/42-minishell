
#include "../minishell.h"

void    ft_exit(t_data *d)
{
    if (d)
        clean_data(d);
    if (d->paths)
        clean_strs(d->paths, 0, 0);
    if (d->env)
        clean_strs(d->env, 0, 0);
    if (d->input)
        free(d->input);
	rl_clear_history();
    free(d);
    exit(0);
}