#include "../minishell.h"

int	pathfinder(t_cmd *cmd, char **env)
{
	while (ft_strncmp("PATH", *env, 4))
		env++;
	cmd->path = *env + 5;
	cmd->cmd_path = ft_split(cmd->path, ':');
	// printf("path[0] = %s\n", cmd->cmd_path[0]);
	return (0);
}

int	exec_1(t_cmd *cmd, char **env, int cmd_i)
{
	int	i;
	char	**scmd;
	char	*tmp;
	char 	*vcmd;

	i = 0;
	pathfinder(cmd, env);
	scmd = ft_split(cmd->cmds[cmd_i], ' ');
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
	clean_strs(0, 0, scmd, cmd->cmd_path);
	return (0);
}

int	ref_sep(t_cmd *cmd, char **env)
{
	int	i;

	i = -1;
	(void) env;
	while (cmd->sep[++i])
	{
		if (!ft_strncmp(cmd->sep[i], "<", 1) || !ft_strncmp(cmd->sep[i], "<<", 2))
			redir_in(cmd, env);
		if (!ft_strncmp(cmd->sep[i], ">", 1) || !ft_strncmp(cmd->sep[i], ">>", 2))
			redir_out();
		if (!ft_strncmp(cmd->sep[i], "|", 1))
		{
			ft_pipe(cmd, env);
		}
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
		else if (exec_1(cmd, env, 0))
			return(1);
	}
	wait(NULL);
	return (0);
}
