/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maderuel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:43:02 by maderuel          #+#    #+#             */
/*   Updated: 2023/12/05 13:46:35 by maderuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	*data;
	char	**new_env;
	int i;

	i = 0;
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (0);
	(void) av;
	if (ac != 1)
	{
		free(data);
		return (0);
	}
	new_env = env_alloc(env);
	while (new_env[i])
	{
		printf("%s\n", new_env[i]);
		i++;
	}
	shell_loop(data, env);
	free(data);
	free(new_env);
	return (0);
}
