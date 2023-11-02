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

	set = "&|;";
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
		if (is_charset(s[i])
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

void	ca_parse(int argc, char **argv, char **env)
{
	char	**cmds;
	char	*sep;

	cmds = ms_split(argv);
	sep = rev_ms_split(argv);
	
}

int	main(int argc, char **argv, char **env)
{
	const char	*prompt;
	char	*input;

	prompt = "$> ";
	while (1)
	{
		input = readline(prompt);
		if (!ft_strncmp(input, "exit", ft_strlen(input)))
			break ;
		printf("YEP : %s\n", input);
		ca_parse(argc, argv, env);
		printf("Ca Parse ?\n");
		printf("Execution !\n");
		free(input);
	}
	free(input);
	return (0);
}
