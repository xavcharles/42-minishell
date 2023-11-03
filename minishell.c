/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:40:29 by xacharle          #+#    #+#             */
/*   Updated: 2023/10/24 15:40:32 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	strs = malloc(sizeof(char *) * (cmd_count(s)));
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

t_cmd	*ca_parse(char *input, char **env)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (clean_strs(1, 0, 0, 0));
	cmd->cmds = ms_split(input);
	if !(cmd->cmds)
		return (clean_strs(2, cmd, 0, 0));
	if (cmd_count(input) > 1)
	{
		cmd->sep = rev_ms_split(input);
		if (!(cmd->sep))
			return (clean_strs(3, cmd, cmd->cmds, 0));
	}
	else
		cmd->sep = NULL;
	if (!valid_sep(cmd->sep))
		return (clean_strs(4, cmd, cmd->cmds, cmd->sep));
	return (cmd);
}

int	main(int argc, char **argv, char **env)
{
	const char	*prompt;
	char	*input;
	t_cmd	*cmd;

	prompt = "$> ";
	while (1)
	{
		input = readline(prompt);
		if (!ft_strncmp(input, "exit", ft_strlen(input)))
			break ;
		printf("YEP : %s\n", input);
		printf("Ca Parse ?\n");
		if (!ca_parse(input, env))
		{
			free(input);
			printf("Error during parsing\n");
			return (0);
		}
		printf("Execution !\n");
		if (!cmd_exec(cmd))
		{
			free(input);
			printf("Error during execution\n");
			return (0);
		}
		free(input);
	}
	free(input);
	return (0);
}
