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

// int	pathfinder(t_cmd *cmd, char **env)
// {
// 	char	**strs;

// 	strs = env;
// 	while (ft_strncmp("PATH", *strs, 4))
// 		env++;
// 	cmd->path = *strs + 5;
// 	cmd->cmd_path = ft_split(cmd->path, ':');
// 	if (!cmd->cmd_path)
// 		return (1);
// 	return (0);
// }

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

	if (cmd->sep)
	{
		strs = cmd->sep;
		while (*strs)
			free(*(strs++));
		free(cmd->sep);
	}
	if (cmd->cmds)
	{
		strs = cmd->cmds;
		while (*strs)
			free(*(strs++));
		free(cmd->cmds);
	}
	if (cmd->cmd_path)
	{
		strs = cmd->cmd_path;
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
	d->cmd->cmds = ms_split(input, "&|");
	if (!d->cmd->cmds)
		return (clean_cmd(d->cmd));
	if (sep_count(input) >= 1)
	{
		d->cmd->sep = rev_ms_split(input, "&|");
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

int	init_ccmd(t_data *d, t_ccmd *cmd)
{
	int		i;
	int		j;
	char	*cmd_args;
	char	**strs;

	i = 0;
	cmd_args = NULL;
	while (d->cmds[i])
	{
		strs = ms_split(d->cmds[i], " \t");
		if (!strs)
			return (1) //implement free error
		if (strs[0] && !ft_strchr(strs[0], "<") && ft_strchr(strs[0], ">"))
		{
			cmd->cmd = ft_strdup(strs[j]);
			if (!cmd->cmd)
				return (1); //implement 
			j = 0;
			while (strs[j] && !ft_strchr(strs[j], "<") && ft_strchr(strs[j], ">"))
				cmd_args = join_w_space(cmd_args, strs[j++]);
			if (!cmd_args)
				return (1); //implement err
			cmd->cmd_arg = ms_split(cmd_args, " ");
		}
	}
}

int	ca_parse(t_data *d, char *input)
{
	d->cmd_count = cmd_count(input);
	d->sep_count = sep_count(input);
	d->seps = rev_ms_split(input, "&|");
	if (!d->seps && d->sep_count)
		return (1); // free a implement
	if (sep_check(d->seps))
		return (1); // free a implement
	d->cmds = ms_split(input, "&|");
	if (!d->cmds)
		return (1);	//free a implement
	d->cmd = malloc(sizeof(t_ccmd) * d->cmd_count);
	if (!d->cmd)
		return (1); //free a implement
	if (init_ccmd(d, d->cmd))
		return (1); //free a iplement
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
		if (!input)
		{
			printf("break 1\n");
			break ;
		}
		if (!ft_strncmp(input, "exit", ft_strlen(input)) && ft_strlen(input))
		{	
			printf("break 2\n");
			break ;
		}
		if (ft_strlen(input))
		{
			add_history(input);
			if (ca_parse(d, input))
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
			clean_cmd(d->cmd);
		}
		free(input);
		usleep(10);
	}
	free(input);
	rl_clear_history();
	printf("exitted\n");
	return (0);
}
