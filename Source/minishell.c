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

int	clean_cmd(t_data *d)
{
	int	i;
	int j;

	i = 0;
	j = -1;
	while (i < d->cmd_count)
	{
		if (d->cmd[i].cmd_arg)
		{
			j = -1;
			while (d->cmd[i].cmd_arg[++j])
				free(d->cmd[i].cmd_arg[j]);
			free(d->cmd[i].cmd_arg);
		}
		if (d->cmd[i].in)
		{
			j = -1;
			while (d->cmd[i].in[++j])
				free(d->cmd[i].in[j]);
			free(d->cmd[i].in);
		}
		if (d->cmd[i].out)
		{	
			j = -1;
			while (d->cmd[i].out[++j])
				free(d->cmd[i].out[j]);
			free(d->cmd[i].out);
		}
		free(d->cmd[i].cmd);
		free(d->cmd[i].prev_op);
		free(d->cmd[i].next_op);
		i++;
	}
	free(d->cmd);
	if (d->seps)
	{
		j = -1;
		while (d->seps[++j])
			free(d->seps[j]);
		free(d->seps);
	}
	if (d->cmds)
	{
		j = -1;
		while (d->cmds[++j])
			free(d->cmds[j]);
		free(d->cmds);
	}
	return (1);
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
	while (d->cmds[i])
	{
		ccmd[i].in = NULL;
		ccmd[i].out = NULL;
		strs = ms_split(d->cmds[i], "\t ");
		if (!strs)
			return (1);
		j = 0;
		in = NULL;
		out = NULL;
		while (strs[j])
		{
			if (!ft_strchr(strs[j], '<') && !ft_strchr(strs[j], '>'))
			{
				cmd_args = NULL;
				ccmd[i].cmd = ft_strdup(strs[j]);
				if (!ccmd[i].cmd)
					return (1); //implement
				while (strs[j] && !ft_strchr(strs[j], '<') && !ft_strchr(strs[j], '>'))
					cmd_args = join_w_space(cmd_args, strs[j++]);
				if (!cmd_args)
					return (1);
				ccmd[i].cmd_arg = ms_split(cmd_args, " ");
				if (!ccmd[i].cmd_arg)
					return (1);
				free(cmd_args);
			}
			else
			{
				while (strs[j] && (!ft_strncmp(strs[j], ">", ft_strlen(strs[j])) || !ft_strncmp(strs[j], ">>", ft_strlen(strs[j]))))
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
				while (strs[j] && !ft_strncmp(strs[j], "<", ft_strlen(strs[j])))
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
			ccmd[i].in = ms_split(in, "\t");
			if (!ccmd[i].in)
				return (1); //malloc error
			free(in);
		}
		if (out)
		{
			ccmd[i].out = ms_split(out, "\t");
			if (!ccmd[i].out)
				return (1); //malloc error
			free(out);
		}
		clean_strs(0, 0, 0, strs);
		i++;
	}
	return (0);
}

int	set_op_pipe(int j, t_ccmd *ccmd, char *input)
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

int	set_op_and(int j, t_ccmd *ccmd, char *input)
{
	if (!ft_strncmp(input + j, "&", 1))
	{
		ccmd->next_op = ft_strdup("&");
		if (!ccmd->next_op)
			return (1); //malloc error
	}
	else if (!ft_strncmp(input + j, "&&", 2))
	{
		ccmd->next_op = ft_strdup("&&");
		if (!ccmd->next_op)
			return (1); //malloc error
	}
	return (0);
}

int	set_prev_op(int j, t_ccmd *ccmd, char *input)
{
	if (!ft_strncmp(input + j, "|", 1))
	{
		ccmd->prev_op = ft_strdup("|");
		if (!ccmd->prev_op)
			return (1); //malloc error
	}
	else if (!ft_strncmp(input + j, "||", 2))
	{
		ccmd->prev_op = ft_strdup("||");
		if (!ccmd->prev_op)
			return (1); //malloc error
	}
	if (!ft_strncmp(input + j, "&", 1))
	{
		ccmd->prev_op = ft_strdup("&");
		if (!ccmd->prev_op)
			return (1); //malloc error
	}
	else if (!ft_strncmp(input + j, "&&", 2))
	{
		ccmd->prev_op = ft_strdup("&&");
		if (!ccmd->prev_op)
			return (1); //malloc error
	}
	return (0);
}

int	set_next_op(t_data *d, char *input)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	d->cmd[i].prev_op = NULL;
	while (d->cmds[i + 1])
	{
		d->cmd[i].next_op = NULL;
		if (j > 0)
			if (set_prev_op(j, d->cmd + i, input))
				return (1);
		j += ft_strlen(d->cmds[i]) + 1;
		if (set_op_pipe(j, d->cmd + i, input))
			return(1); //maloc error
		if (set_op_and(j, d->cmd + i, input))
			return(1); //maloc error
		i++;
	}
	if (i > 0)
		if (set_prev_op(j, d->cmd + i, input))
			return (1);
	d->cmd[i].next_op = NULL;
	return (0);
}

int	ca_parse(t_data *d, char *input)
{
	int	i;
	int	j;

	i = 0;
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	if (input [i] == '&' || input[i] == '|')
		return (1); //parse error 1st char == & ou && ou | ou ||
	d->cmd_count = cmd_count(input, "|&");
	d->sep_count = sep_count(input, "|&");
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
	i = 0;
	printf("\n\nDans la fonction ca_parse : \n\n");
	while (i < d->cmd_count)
	{
		printf("cmd = %s\n", d->cmd[i].cmd);
		j = 0;
		printf("cmd with arg : ");
		while (d->cmd[i].cmd_arg && d->cmd[i].cmd_arg[j])
		{
			printf("%s ", d->cmd[i].cmd_arg[j]);
			j++;
		}
		printf("\n");
		j = 0;
		printf("in : ");
		while (d->cmd[i].in && d->cmd[i].in[j])
		{
			printf("%s ", d->cmd[i].in[j]);
			j++;
		}
		printf("\n");
		j = 0;
		printf("out : ");
		while (d->cmd[i].out && d->cmd[i].out[j])
		{
			printf("%s ", d->cmd[i].out[j]);
			j++;
		}
		printf("\n");
		printf("prev op = %s\n", d->cmd[i].prev_op);
		printf("next op = %s\n", d->cmd[i].next_op);
		i++;
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
				clean_cmd(d);
				rl_clear_history();
				printf("Error during parsing\n");
				return (1);
			}
			if (cmd_exec(d))
			{
				free(input);
				clean_cmd(d);
				rl_clear_history();
				printf("Error during execution\n");
				return (1);
			}
			clean_cmd(d);
		}
		free(input);
	}
	(void) env;
	free(input);
	rl_clear_history();
	printf("exitted\n");
	return (0);
}
