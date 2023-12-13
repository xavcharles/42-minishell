#include "../minishell.h"

void	kido(t_pipe pipe, t_data *d, int cc)
{
	dup2(pipe.end[1], 1);
	close(pipe.end[1]);
	close(pipe.end[0]);
	if (exec_1(d, cc))
		exit(EXIT_FAILURE);
}

void	daron(t_pipe pipe, t_data *d, int cc)
{
	dup2(pipe.end[0], 0);
	close(pipe.end[0]);
	close(pipe.end[1]);
	if (exec_1(d, cc))
		exit(EXIT_FAILURE);
}

int	ft_pipe(t_data *d, int cc)
{
	t_pipe	p;
	pid_t	pid;

	pipe(p.end);
	pid = fork();
	if (pid < 0)
		return (printf("fork err") * 0);
	if (pid == 0)
		kido(p, d, cc);
	daron(p, d, 1);
	wait(NULL);
	return (0);
}
