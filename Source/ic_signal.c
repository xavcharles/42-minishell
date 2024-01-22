/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ic_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:30:14 by xacharle          #+#    #+#             */
/*   Updated: 2024/01/22 12:55:50 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	cc_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_ret = 130;
}

static void	cc_hd_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	close (0);
	rl_redisplay();
	g_ret = 130;
}

static void	bs_handler(int sig)
{
	write(1, "\n", 1);
	ft_dprintf(2, "Quit (core dumped)\n");
	g_ret = 131;
	(void)sig;
}

void	ic_sigs(int sig)
{
	if (sig == 1)
		signal(SIGINT, cc_handler);
	if (sig == 2)
		signal(SIGQUIT, bs_handler);
	if (sig == 3)
		signal(SIGINT, cc_hd_handler);
}
