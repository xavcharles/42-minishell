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
			clean_data(d);
		}
		free(input);
		usleep(10);
	}
	free(input);
	rl_clear_history();
	printf("exitted\n");
	return (0);
}
