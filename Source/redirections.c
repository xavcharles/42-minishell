#include "../minishell.h"

int	redir_in(t_cmd *cmd, char **env)
{
	t_pipe	p;
	char	*file;

	file = cmd->cmds[1];
	p.f1 = open(file, O_RDONLY);
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
