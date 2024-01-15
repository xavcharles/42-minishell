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

void	print_contenu(t_data *d)
{
	int	i;
	int	j;

	i = 0;
	printf("\n       ************      \nDans la fonction ca_parse : \n\n");
	while (i < d->cmd_count)
	{
		printf("cmd = %s\n", d->cmd[i].cmd);
		j = 0;
		printf("cmd with arg : ");
		while (d->cmd[i].cmd_arg && d->cmd[i].cmd_arg[j])
		{
			printf("arg%d=%s ", j, d->cmd[i].cmd_arg[j]);
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
		printf("\n       ************      \n\n");
		i++;
	}
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
	print_contenu(d);    // ne pas oublier de retirer
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
		signal(SIGQUIT, SIG_IGN);
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
			if (!ca_parse(d, input))
			{
				if (cmd_exec(d))
					printf("Error during execution\n");
				clean_data(d);
			}
			else
				printf("Error during parsing\n");		
		}
		free(input);
		usleep(10);
	}
	free(input);
	rl_clear_history();
	printf("exitted\n");
	return (0);
}
