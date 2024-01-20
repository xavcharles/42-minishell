/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:44:12 by xacharle          #+#    #+#             */
/*   Updated: 2024/01/18 16:16:09 by maderuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <unistd.h>
# include <errno.h>

typedef struct s_ccmd
{
	char	*cmd;
	char	**cmd_arg;
	char	**in;
	char	**out;
	char	*next_op;
	char	*prev_op;
}	t_ccmd;

typedef struct s_pipe
{
	pid_t	pid1;
	pid_t	pid2;
	int		end[2];
	int		f1;
	int		f2;
}	t_pipe;

typedef struct s_data
{
	t_ccmd	*cmd;
	char	**cmds;
	char	**seps;
	char	**paths;
	char	**env;
	char	*input;
	int		cmd_count;
	int		sep_count;
	int		err;
	int		std_out;
	int		std_in;
	t_pipe	*p;
}	t_data;

extern int	g_ret;

void	clean_strs(char	**strs1, char **strs2, char **strs3);
int		clean_data(t_data *d);
void	clean_ccmd(t_ccmd *ccmd);
int		init_ccmd(t_data *d, t_ccmd *ccmd);
int		set_next_op(t_data *d, char *input);
int		shell_loop(t_data *d);
int		pathfinder(t_data *d);
int		env_cpy(t_data *data, char **env);
char	*join_w_space(char *s1, char *s2);
char	*join_w_tab(char *s1, char *s2);
void	ic_sigs(int sig);
int		is_charset(char c, char *set);
int		cmd_count(char const *s, char *set);
int		sep_count(char const *s, char *set);
char	**ms_split(char *s, char *set);
char	**rev_ms_split(char *s, char *set);
int		redir_in(t_data *d, t_ccmd *cmd);
int		sep_check(char **seps);
int		exec_1(t_data *d, int cc);
int		cmd_exec(t_data *d);
int		redir_out(t_data *d, t_ccmd *cmd);
int		ft_pipe(t_data *d, int cc);
int		print_env(t_data *d);
int		ft_export(t_data *d, int cc);
int		ft_unset(t_data *d, int cc);
int		ft_echo(t_data *d, int cc);
int		cd_builtin(t_data *d, int cc);
int		pwd_builtin(t_data *d, int cc);
int		sep_check(char **seps);
int		input_check(t_data *strs);
int		check_esp(char *str, int *i);
int		check_pipe(char *str, int *i);
void	init_zero(t_data *d);
int		check_first(char *input);
int		check_firstbis(char *input);
void	ft_exit(t_data *d, int n);
int		is_builtin(t_data *d, int cc);
int		strs_len(char **strs);
int		find_var(char **env, char *var);
int		is_builtin1(t_data *d, int cc);
int		is_builtin2(t_data *d, int cc);
int		par_cd(t_data *d, int cc);
int		par_export(t_data *d, int cc);
int		par_unset(t_data *d, int cc);
char	**ft_tabjoin(char **tab, char *s);
char	**ft_subtab(char **tab, char *s);
int	dollar_search(t_data *d);
int	s_quote1(char **tmp, char *arg, int *k);
int	d_quote1(t_data *d, char ***strs, char *arg, int *k);
int	dollar_replace(t_data *d, char **s, int op, int *start);
int	len_varval(t_data *d, char *str, int op);
char	*env_varval(t_data *d, char *str);
int		exec_builtin(t_data *d, int cc);
int		ven_larlav(t_data *d, char *str);
size_t	ft_trslen(const char *s);
int		dollar_replace2(t_data *d, char **s, int op, int start);
int		find_match(t_data *d, int *i, char **tmp, char *str);
char	*recreate_str(t_data *d, int start, char **s, char **tmp);
char	**quot_split(char *s, char *set);
int		quot_count(char *s, char *set);
int	loop_2(char *str, char **cmd_arg, char **in, char **out);
int	fill_justthesign(char *str, char **in, char **out, int *i);
int	ministrlen(char **strs);
char	*minijoin(char **strs);
int	dollar_loop(t_data *d, t_ccmd *ccmd, char **rep, int *k);
int	dollar_inout(t_data *d, t_ccmd *cmd);
int	do_squote(t_data *d, t_ccmd *ccmd, char **rep, int *k);
int	print_stxerr(char c1, char c2);

#endif
