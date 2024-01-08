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

void	data_zero(t_data *d)
{
	d->cmd = NULL;
	d->cmds = NULL;
	d->seps = NULL;
	d->cmd_count = 0;
	d->sep_count = 0;
	d->err = 0;
	d->p = 0;
}

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
	int	i;
	int	j;

	data_zero(d);
	if (first_char(input))
		return (1);
	d->input = input;
	d->cmd_count = cmd_count(input, "|&");
	d->sep_count = sep_count(input, "|&");
	d->seps = rev_ms_split(input, "&|");
	if (!d->seps && d->sep_count)
		return (printf("malloc error"), 1);
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
	clean_data(d);
	return (0);
}

int	shell_loop(t_data *d)
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
				// free(input);
				// clean_data(d);
				// rl_clear_history();
				printf("Error during parsing\n");
				// return (1);
			}
			// if (cmd_exec(d))
			// {
			// 	free(input);
			// 	clean_data(d);
			// 	rl_clear_history();
			// 	printf("Error during execution\n");
			// 	return (1);
			// }
			// clean_data(d);
		}
		free(input);
		usleep(10);
	}
	free(input);
	rl_clear_history();
	printf("exitted\n");
	return (0);
}
