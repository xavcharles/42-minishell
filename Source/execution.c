#include "../minishell.h"

int	exec_1(t_cmd *cmd, char **env)
{
	int		i;
	char	**scmd;
	char	*tmp;
	char 	*vcmd;

	i = 0;
	scmd = ft_split(cmd->cmds[0], ' ');
	while (cmd->cmd_path[i])
	{
		tmp = ft_strjoin(cmd->cmd_path[i], "/");
		vcmd = ft_strjoin(tmp, scmd[0]);
		free(tmp);
		if (!access(vcmd, X_OK))
		{
			if (execve(vcmd, scmd, env) == -1)
			{
				perror("Minishell");
				clean_strs(0, 0, scmd, 0);
				free(vcmd);
				return (1);
			}
		}
		free(vcmd);
		i++;
	}
	clean_strs(0, 0, scmd, 0);
	return (0);
}

int	ref_sep(t_cmd *cmd, char **env)
{
	int	i;

	i = -1;
	(void) env;
	while (cmd->sep[++i])
	{
		if (!ft_strncmp(cmd->sep[i], "|", 1))
			printf("pipe \n");
		else if (!ft_strncmp(cmd->sep[i], "<", 1))
			printf("< \n");
	}
	return (0);
}

int	cmd_exec(t_cmd *cmd, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (cmd->sep)
			ref_sep(cmd, env);
		if (exec_1(cmd, env))
			return(1);
	}
	wait(NULL);
	return (0);
}
