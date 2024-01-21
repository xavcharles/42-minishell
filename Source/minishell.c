/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                   +:+ +:+         +:+     */
/*   By: xacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:40:29 by xacharle          #+#    #+#             */
/*   Updated: 2024/01/20 17:41:51 by maderuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	first_char(char	*input)
{
	int	i;

	i = 0;
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	if (input[i] == '&' || input[i] == '|')
		return (check_first(input + i), 1);
	else if (input[i] == ';')
		return (check_firstbis(input + i), 1);
	return (0);
}

int	ca_parse(t_data *d, char *input)
{
	if (first_char(input))
		return (1);
	d->input = input;
	d->cmd_count = cmd_count(input, "|&");
	d->sep_count = sep_count(input, "|&");
	d->seps = rev_ms_split(input, "&|");
	if (!d->seps && d->sep_count)
		return (printf("Minishell: Failed Malloc in ca_parse\n"), 1);
	d->cmds = ms_split(input, "&|");
	if (!d->cmds)
		return (clean_data(d), 1);
	d->cmd = malloc(sizeof(t_ccmd) * d->cmd_count);
	if (!d->cmd)
		return (clean_data(d), 1);
	if (set_next_op(d, input))
		return (clean_data(d), 1);
	if (init_ccmd(d, d->cmd))
		return (clean_data(d), 1);
	if (dollar_search(d))
		return (clean_data(d), 1);
	return (0);
}

char	*prompt_pwd(t_data *d)
{
	int		i;
	char	**s;
	char	*ret;

	i = -1;
	while (d->env[++i])
		if (!ft_strncmp(d->env[i], "PWD", 3))
			break ;
	s = ft_split(d->env[i], '=');
	free(s[0]);
	ret = ft_strjoin(s[1], "$> ");
	free(s[1]);
	free(s);
	return (ret);
}

int	shell_loop2(t_data *d, char *input)
{
	add_history(input);
	if (!ca_parse(d, input))
	{
		signal(SIGINT, SIG_IGN);
		if (cmd_exec(d))
			printf("Error during execution\n");
		clean_data(d);
	}
	else
		g_ret = 2;
	return (0);
}

int	shell_loop(t_data *d)
{
	char		*prompt;
	char		*input;

	while (1)
	{
		prompt = prompt_pwd(d);
		ic_sigs(1);
		signal(SIGQUIT, SIG_IGN);
		input = readline(prompt);
		free(prompt);
		if (!input)
			break ;
		if (!ft_strncmp(input, "exit", ft_strlen(input)) && ft_strlen(input))
			break ;
		if (ft_strlen(input))
			shell_loop2(d, input);
		free(input);
		free(prompt);
		usleep(10);
	}
	free(input);
	free(prompt);
	rl_clear_history();
	printf("exitted\n");
	return (0);
}
