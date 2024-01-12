
#include "../minishell.h"

static void    cc_handler(int sig)
{
	(void)sig;
    write(1, "\n", 1);
    rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	bs_handler(int sig)
{
    write(1, "\n", 1);
	printf("Quit (core dumped)\n");
	g_ret = 131;
	(void)sig;
}

void	ic_sigs(int sig)
{
	if (sig == 1)
	{
		signal(SIGINT, cc_handler);
	}
	if (sig == 2)
	{
		signal(SIGQUIT, bs_handler);
	}
}
