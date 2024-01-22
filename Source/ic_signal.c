/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ic_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:30:14 by xacharle          #+#    #+#             */
/*   Updated: 2024/01/22 19:56:57 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handler_5(int sig)
{
	g_ret = 130;
	ft_dprintf(2, "\n");
	close(0);
	(void)sig;
}

static void	cc_handler(int sig)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_ret = 130;
	(void)sig;
}

/*
static void	cc_hd_handler(int sig)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	close (0);
	rl_redisplay();
	g_ret = 130;
	(void)sig;
}
*/
static void	handler_2(int sig)
{
	write(1, "\n", 1);
	g_ret = 130;
	(void)sig;
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
	{
		signal(SIGINT, cc_handler);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 2)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 3)
	{
		signal(SIGINT, handler_5);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 4)
	{
		signal(SIGINT, handler_2);
		signal(SIGQUIT, bs_handler);
	}
	if (sig == 5)
		signal(SIGINT, handler_5);
}
