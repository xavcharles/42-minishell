#include "../minishell.h"

int	ft_echo(t_data *d, int cc)
{
	int		i;
	char	*str;

	i = 1;
	if (!ft_strncmp(d->cmd[cc].cmd_arg[1], "-n", 2))
		i = 2;
	while (d->cmd[cc].cmd_arg[i])
	{
		if (d->cmd[cc].cmd_arg[i][0] == '"')
		{
			str = ft_strtrim(d->cmd[cc].cmd_arg[i], "\"");
			if (!str)
				return (exit(1), 1);
			ft_putstr_fd(str, 1);
			free(str);
		}
		else if (d->cmd[cc].cmd_arg[i][0] == '\'')
		{
			str = ft_strtrim(d->cmd[cc].cmd_arg[i], "'");
			if (!str)
				return (exit(1), 1);
			ft_putstr_fd(str, 1);
			free(str);
		}
		else
			ft_putstr_fd(d->cmd[cc].cmd_arg[i], 1);
		i++;
		if (d->cmd[cc].cmd_arg[i])
			write(1, " ", 1);
	}
	if (ft_strncmp(d->cmd[cc].cmd_arg[1], "-n", 2))
		write(1, "\n", 1);
	return (ft_exit(d, 0), 0);
}
