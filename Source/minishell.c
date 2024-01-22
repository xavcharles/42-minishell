/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                   +:+ +:+         +:+     */
/*   By: xacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:40:29 by xacharle          #+#    #+#             */
/*   Updated: 2024/01/22 18:14:46 by maderuel         ###   ########.fr       */
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
		return (ft_dprintf(2, "Minishell: Failed Malloc in ca_parse\n"), 1);
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

int	m_get_pwd(t_data *d)
{
	char	s[1064];
	char	*tmp;
	int		i;

	if (d->pwd)
		free(d->pwd);
	tmp = getcwd(s, 1064);
	i = ft_strlen(tmp);
	d->pwd = ft_strdup(tmp);
	return (0);
}

int	shell_loop2(t_data *d, char *input)
{
	add_to_history(input);
	if (!ca_parse(d, input))
	{
		signal(SIGINT, SIG_IGN);
		if (!init_heredoc(d))
		{
			ic_sigs(1);
			if (cmd_exec(d))
				ft_dprintf(2, "Error during execution\n");
		}
		clean_data(d);
	}
	else
		g_ret = 2;
	return (0);
}

int	shell_loop(t_data *d)
{
	char		*input;

	while (1)
	{
		ic_sigs(1);
		signal(SIGQUIT, SIG_IGN);
		input = readline("> ");
		if (!input)
			break ;
		if (ft_strlen(input) && !ft_strcmp(input, "exit"))
			break ;
		if (ft_strlen(input))
			shell_loop2(d, input);
		free(input);
		usleep(10);
	}
	free(input);
	rl_clear_history();
	return (g_ret);
}
