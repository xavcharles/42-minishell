/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maderuel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 15:30:54 by maderuel          #+#    #+#             */
/*   Updated: 2024/01/20 15:32:35 by maderuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

char	**ft_tabjoin(char **tab, char *s)
{
	int		i;
	int		j;
	char	**n_tab;

	i = 0;
	j = 0;
	(void) s;
	while (tab[i])
		i++;
	n_tab = malloc(sizeof(char *) * (i + 2));
	if (n_tab == NULL)
		return (NULL);
	while (j < i)
	{
		n_tab[j] = ft_strdup(tab[j]);
		free(tab[j]);
		j++;
	}
	free(tab);
	n_tab[j] = ft_strdup(s);
	n_tab[j + 1] = NULL;
	return (n_tab);
}
