/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:12:24 by xacharle          #+#    #+#             */
/*   Updated: 2024/01/22 17:55:35 by maderuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	history_restore(void)
{
	char	*str;
	char	*tmp;
	int		fd;

	fd = open("/tmp/mini_hist", O_RDONLY);
	if (fd == -1)
		return ;
	str = get_next_line(fd);
	if (!str)
	{
		close(fd);
		return ;
	}
	while (str)
	{
		tmp = str;
		str = ft_strtrim(str, "\n");
		free(tmp);
		add_history(str);
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
}

int	add_to_history(char *input)
{
	int	fd;

	fd = open("/tmp/mini_hist", O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (1);
	add_history(input);
	ft_dprintf(fd, "%s\n", input);
	close(fd);
	return (0);
}
