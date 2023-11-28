/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                   +:+ +:+         +:+     */
/*   By: xacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:40:29 by xacharle          #+#    #+#             */
/*   Updated: 2023/10/24 15:40:32 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pathfinder(t_cmd *cmd, char **env)
{
	while (ft_strncmp("PATH", *env, 4))
		env++;
	cmd->path = *env + 5;
	cmd->cmd_path = ft_split(cmd->path, ':');
	if (!cmd->cmd_path)
		return (1);
	return (0);
}

t_cmd	*clean_strs(int id, t_cmd *cmd, char **cmds, char **sep)
{
	char	**strs;

	if (id == 1 || id == 2 || id == 3)
		printf("Malloc error during parsing\n");
	if (id == 4)
		printf("Invalid separators within command \n");
	strs = sep;
	if (sep)
	{
		while (*strs)
			free(*(strs++));
		free(sep);
	}
	strs = cmds;
	if (cmds)
	{
		while (*strs)
			free(*(strs++));
		free(cmds);
	}
	if (cmd)
		free(cmd);
	return (0);
}

int	clean_cmd(t_cmd *cmd)
{
	char	**strs;

	strs = cmd->sep;
	if (cmd->sep)
	{
		while (*strs)
			free(*(strs++));
		free(cmd->sep);
	}
	strs = cmd->cmds;
	if (cmd->cmds)
	{
		while (*strs)
			free(*(strs++));
		free(cmd->cmds);
	}
	strs = cmd->cmd_path;
	if (cmd->cmd_path)
	{
		while (*strs)
			free(*(strs++));
		free(cmd->cmd_path);
	}
	free(cmd);
	return (1);
}

int	ca_parse(t_data *d, char *input, char **env)
{
	d->cmd = malloc(sizeof(t_cmd));
	if (!d->cmd)
		return (printf("Failed malloc for t_cmd\n"));
	d->cmd->cmds = ms_split(input);
	if (!d->cmd->cmds)
		return (clean_cmd(d->cmd));
	if (sep_count(input) >= 1)
	{
		d->cmd->sep = rev_ms_split(input);
		if (!(d->cmd->sep))
			return (clean_cmd(d->cmd));
	}
	else
		d->cmd->sep = NULL;
	if (pathfinder(d->cmd, env))
	{
		return (clean_cmd(d->cmd));
	}
	return (0);
}


int	shell_loop(t_data *d, char **env)
{
	const char	*prompt;
	char	*input;

	prompt = "$> ";
	while (1)
	{
		ic_sigs(1);
		input = readline(prompt);
		if (!ft_strncmp(input, "exit", ft_strlen(input)))
			break ;
		if (input)
		{
			add_history(input);
			if (ca_parse(d, input, env))
			{
				free(input);
				rl_clear_history();
				printf("Error during parsing\n");
				return (1);
			}
			if (cmd_exec(d->cmd, env))
			{
				free(input);
				clean_cmd(d->cmd);
				rl_clear_history();
				printf("Error during execution\n");
				return (1);
			}
		}
		free(input);
		clean_cmd(d->cmd);
	}
	free(input);
	rl_clear_history();
	return (0);
}
