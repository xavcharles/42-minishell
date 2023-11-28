#include "../minishell.h"
void	kido(t_pipe data, t_cmd *cmd, char **env)
{
	dup2(data.end[1], 1);
	close(data.end[1]);
	close(data.end[0]);
	exec_1(cmd, env, 0);
	exit(EXIT_FAILURE);
}

void	daron(t_pipe data, t_cmd *cmd, char **env)
{
	dup2(data.end[0], 0);
	close(data.end[0]);
	close(data.end[1]);
	exec_1(cmd, env, 1);
	exit(EXIT_FAILURE);
}

int	ft_pipe(t_cmd *cmd, char **env)
{
	t_pipe	data;
	pid_t	pid;

	pipe(data.end);
	pid = fork();
	if (pid < 0)
		return (printf("fork err") * 0);
	if (pid == 0)
		kido(data, cmd, env);
	daron(data, cmd, env);
	wait(NULL);
	return (0);
}
