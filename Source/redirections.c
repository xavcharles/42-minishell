#include "../minishell.h"

int	redir_out(t_cmd *cmd, char **env, int i)
{
	t_pipe	p;
	char	*file;

	file = cmd->cmds[i + 1];
	if (cmd->sep[i][0] == '>')
		p.f2 = open(file, O_CREAT | O_RDWR | O_TRUNC, 0777);
	else
		p.f2 = open(file, O_CREAT | O_RDWR | O_APPEND, 0777);
	if (p.f2 < 0)
	{
		clean_strs(0, cmd, cmd->cmds, cmd->sep);
		printf("file not found\n");
		return (1);
	}
	dup2(p.f2, 1);
	close(p.f2);
	exec_1(cmd, env, 0);
	return (0);
}

int	get_doc(char *end, int *p_fd)
{
	char *str;

	close(p_fd[0]);
	while (1)
	{
		str = readline("here_doc $>");
		if (ft_strncmp(str, end, ft_strlen(end)) == 0)
		{
			free(str);
			return (0);
		}
		ft_putstr_fd(str, p_fd[1]);
		free(str);
	}
}

int	here_doc(char *end)
{
	int	p_fd[2];
	pid_t	pid;

	if (pipe(p_fd) < 0)
		return (1);
	pid = fork();
	if (pid < 0)
		return (2);
	if (pid == 0)
		get_doc(end, p_fd);
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		close(p_fd[0]);
		wait(NULL);
	}
	return (0);
}

int	redir_in(t_cmd *cmd, char **env, int i)
{
	t_pipe	p;
	char	*file;

	file = cmd->cmds[i + 1];
	if (ft_strncmp(cmd->sep[i], "<<", 2))
		p.f1 = open(file, O_RDONLY);
	else
		here_doc(cmd->cmds[i]);
	if (p.f1 < 0)
	{
		clean_strs(0, cmd, cmd->cmds, cmd->sep);
		printf("file not found\n");
		return (1);
	}
	dup2(p.f1, 0); 
	close(p.f1);
	exec_1(cmd, env, 0);
	return(0);
}
