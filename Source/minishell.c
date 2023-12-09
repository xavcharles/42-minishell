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
			cmd->cmd = ft_strdup(strs[0]);
			if (!cmd->cmd)
				return (1); //implement 
			j = 0;
			while (strs[j] && !ft_strchr(strs[j], "<") && ft_strchr(strs[j], ">"))
				cmd_args = join_w_space(cmd_args, strs[j++]);
			if (!cmd_args)
				return (1); //implement err
			cmd->cmd_arg = ms_split(cmd_args, " ");
			if (!cmd->cmd_arg)
				return (1); //err
		}
		else if (strs[0])
		{
			
		}
	}
}

int	init_ccmd(t_data *d, t_ccmd *ccmd)
{
	int	i;
	int	j;
	char	*cmd_args;
	char	*in;
	char	*out;
	char	**strs;

	i = 0;
	cmd_args = NULL;
	while (d->cmds[i])
	{
		strs = md_split(d->cmds[i], "\t ");
		if (!strs)
			return (1);
		j = 0;
		in = NULL;
		out = NULL;
		while (strs[j])
		{
			if (!ft_strchr(strs[j], "<") && !ft_strchr(strs[j], ">"))
			{
				ccmd[i]->cmd = ft_strdup(strs[j]);
				if (!ccmd[i]->cmd)
					return (1); //implement
				while (strs[j] && !ft_strchr(strs[j], "<") && !ft_strchr(strs[j], ">"))
					cmd_args = join_w_space(cmd_args, strs[j++]);
				if (!cmd_args)
					return (1);
				ccmd[i]->cmd_arg = ms_split(cmd_args, " ");
				if (!ccmd[i]->cmd_arg)
					return (1);
				free(cmd_args);
			}
			else
			{
				while (!ft_strncmp(strs[j], ">", ft_strlen(strs[j])) || !ft_strncmp(strs[j], ">>", ft_strlen(strs[j])))
				{
					j++;
					if (!strs[j])
						return (1); //parse error
					out = join_w_space(out, strs[j - 1]);
					if (!out)
						return (1); //malloc error
					out = join_w_tab(out, strs[j]);
					if (!out)
						return (1); //malloc error
					j++;
				}
				while (!ft_strncmp(strs[j], "<", ft_strlen(strs[j])))
				{
					j++;
					if (!strs[j])
						return (1); //parse error
					in = join_w_space(in, strs[j - 1]);
					if (!in)
						return (1); //malloc error
					in = join_w_tab(in, strs[j]);
					if (!in)
						return (1); //malloc error
					j++;
				}
			}
		}
		if (in)
		{
			ccmd[i]->in = ms_split(in, "\t");
			if (!ccmd[i]->in)
				return (1); //malloc error
			free(in);
		}
		if (out)
		{
			ccmd[i]->out = ms_split(out, "\t");
			if (!ccmd[i]->out)
				return (1); //malloc error
			free(out);
		}
		clean_strs(0, 0, 0, strs);
		i++;
	}
}

int	set_op_pipe(int j, t_ccmd ccmd, char *input)
{
	if (!ft_strncmp(input + j, "|", 1))
	{
		ccmd->next_op = ft_strdup("|");
		if (!ccmd->next_op)
			return (1); //malloc error
	}
	else if (!ft_strncmp(input + j, "||", 2))
	{
		ccmd->next_op = ft_strdup("||");
		if (!ccmd->next_op)
			return (1); //malloc error
	}
	return (0);
}

int	set_op_and(int j, t_ccmd ccmd, char *input)
{
	if (!ft_strncmp(input + j, "&", 1))
	{
		ccmd->next_op = ft_strdup("&");
		if (!ccmd->next_op)
			return (1); //malloc error
	}
	else if (!ft_strncmp(input + j, "&&", 1))
	{
		ccmd->next_op = ft_strdup("&&");
		if (!ccmd->next_op)
			return (1); //malloc error
	}
	return (0);
}

int	set_next_op(t_data *d, char *input)
{
	int	i;
	int	j;

	i = 0;
	while (d->cmds[i + 1])
	{
		j = ft_strlen(d->cdms[i]);
		while (input[j] == ' ' || input[j] == '\t')
			j++;
		if (set_op_pipe(j, d->cmd[i], input))
			return(1); //maloc error
		if (set_op_and(j, d->cmd[i], input))
			return(1); //maloc error
		i++;
	}
	return (0);
}

int	ca_parse(t_data *d, char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	if (ft_strchr(input[i], "&") || ft_strchr(input[i], "|"))
		return (1); //parse error 1st char == & ou && ou | ou ||
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
	if (set_next_op(d, input))
		return (1); //malloc error
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
