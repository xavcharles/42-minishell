
#include "../minishell.h"

static void    cc_handler(int sig)
{
	(void)sig;
    write(1, "\n", 1);
    rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ic_sigs(int sig)
{
	if (sig == 1)
	{
		signal(SIGINT, cc_handler);
	}
}
