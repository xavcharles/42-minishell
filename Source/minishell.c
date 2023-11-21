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

int		is_charset(char c)
{
	int	i;
	char	*set;

	set = "&|<>";
	i = 0;
	while (set[i])
	{
		if (c == set[i++])
			return (1);
	}
	return (0);
}

int	cmd_count(char const *s)
{
	int	i;
	int	w;

	i = 0;
	w = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (is_charset(s[i]))
			i++;
		else
		{
			while (s[i] && !is_charset(s[i]))
				i++;
			w++;
		}
	}
	return (w);
}

int	sep_count(char const *s)
{
	int	i;
	int	w;

	i = 0;
	w = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (!is_charset(s[i]))
			i++;
		else
		{
			while (s[i] && is_charset(s[i]))
				i++;
			w++;
		}
	}
	return (w);
}

char	**ms_split(char *s)
{
	int		w;
	int		i;
	int		start;
	char	**strs;

	strs = malloc(sizeof(char *) * (cmd_count(s) + 1));
	if (!strs)
		return (NULL);
	i = 0;
	w = 0;
	while (s && s[i])
	{
		if (is_charset(s[i]))
			i++;
		else
		{
			start = i;
			while (s[i] && !is_charset(s[i]))
				i++;
			strs[w] = ft_substr(s, start, i - start);
			w++;
		}
	}
	strs[w] = NULL;
	return (strs);
}

char	**rev_ms_split(char *s)
{
	int		w;
	int		i;
	int		start;
	char	**strs;

	strs = malloc(sizeof(char *) * (sep_count(s) + 1));
	if (!strs)
		return (NULL);
	i = 0;
	w = 0;
	while (s && s[i])
	{
		if (!is_charset(s[i]))
			i++;
		else
		{
			start = i;
			while (s[i] && is_charset(s[i]))
				i++;
			strs[w] = ft_substr(s, start, i - start);
			w++;
		}
	}
	strs[w] = NULL;
	return (strs);
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

int	ca_parse(t_data *d, char *input, char **env)
{
	(void) env;
	d->cmd = malloc(sizeof(t_cmd));
	if (!d->cmd)
		return (clean_strs(1, 0, 0, 0), 0);
	d->cmd->cmds = ms_split(input);
	if (!d->cmd->cmds)
		return (clean_strs(2, d->cmd, 0, 0), 0);
	if (sep_count(input) >= 1)
	{
		d->cmd->sep = rev_ms_split(input);
		if (!(d->cmd->sep))
			return (clean_strs(3, d->cmd, d->cmd->cmds, 0), 0);
	}
	else
		d->cmd->sep = NULL;
	d->cmd->cmd_path = NULL;
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
	return (0);
}

int	shell_loop(t_data *d, char **env)
{
	const char	*prompt;
	char	*input;

	prompt = "$> ";
	while (1)
	{
		input = readline(prompt);
		if (!ft_strncmp(input, "exit", ft_strlen(input)))
			break ;
		ca_parse(d, input, env);
		if (cmd_exec(d->cmd, env))
		{
			free(input);
			printf("Error during execution\n");
			return (1);
		}
		free(input);
		clean_cmd(d->cmd);
	}
	free(input);
	return (0);
}
