/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:44:12 by xacharle          #+#    #+#             */
/*   Updated: 2023/12/05 13:41:08 by maderuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

extern int	g_sig;

typedef	struct s_cmd
{
	char 	**cmds;
	char	**sep;
	char 	**cmd_path;
	char 	*path;
	struct	s_data *data;
	void	*next;
}	t_cmd;

typedef struct	s_ccmd
{
	char	*cmd;
	char	**cmd_arg;
	char	**in;
	char	**out;
	char	*next_op;
}	t_ccmd;

typedef struct	s_pipe
{
	pid_t	pid1;
	pid_t	pid2;
	int		end[2];
	int		f1;
	int		f2;
}	t_pipe;

typedef struct	s_data
{
	t_ccmd	*cmd;
	char	**cmds;
	char	**seps;
	char 	**paths;
	char	**env;
	int		cmd_count;
	int		sep_count;
	int		err;
	t_pipe	*p;
}	t_data;

t_cmd	*clean_strs(int id, t_cmd *cmd, char **cmds, char **sep);
<<<<<<< HEAD
int	exec_1(t_cmd *cmd, char **env, int cmd_i);
int	cmd_exec(t_cmd *cmd, char **env);
int	redir_in(t_cmd *cmd, char **env);
int	shell_loop(t_data *d, char **env);
int	pathfinder(t_cmd *cmd, char **env);
int ft_pipe(t_cmd *d, char **env);
char **env_alloc(char **env);
=======
int		cmd_exec(t_cmd *cmd, char **env);
int		redir_in(t_data *d, char **env);
int		shell_loop(t_data *d, char **env);
int		pathfinder(t_cmd *cmd, char **env);
void	ic_sigs(int sig);
int		is_charset(char c, char *set);
int		cmd_count(char const *s, char *set);
int		sep_count(char const *s, char *set);
char	**ms_split(char *s, char *set);
char	**rev_ms_split(char *s, char *set);
int	sep_check(char **seps);
>>>>>>> xavrestart

#endif
