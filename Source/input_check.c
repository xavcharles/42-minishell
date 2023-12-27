
#include "../minishell.h"

int	check_lessthan(char *str)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	while (str[i] && str[i] == '<')
		i++;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (!str[i])
		return (printf("minishell: syntax error near unexpected token `newline'\n"));
	while (str[i + n] == '<' && n < 3)
		n++;
	if (n == 3)
		return (printf("minishell: syntax error near unexpected token `<<<'\n"));
	if (n == 2)
		return (printf("minishell: syntax error near unexpected token `<<'\n"));
	if (n == 1)
	{
		if (!is_charset(str[i + n], "&|;>"))
			return (printf("minishell: syntax error near unexpected token `<'\n"));
		else
			return (printf("minishell: syntax error near unexpected token `<%c'\n", str[i + n]));
	}
	while (str[i + n] == '&' && n < 2)
		n++;
	if (n == 2)
		return (printf("minishell: syntax error near unexpected token `&&'\n"));
	if (n == 1)
	{
		if (str[i + n] == '>' && str[i + n + 1] == '>')
			return (printf("minishell: syntax error near unexpected token `&>>'\n"));
		else
			return (printf("minishell: syntax error near unexpected token `&'\n"));
	}
	while (str[i + n] == '|' && n < 2)
		n++;
	if (n == 2)
		return (printf("minishell: syntax error near unexpected token `||'\n"));
	if (n == 1)
	{
		if (str[i + n] == '&')
			return (printf("minishell: syntax error near unexpected token `|&'\n"));
		else
			return (printf("minishell: syntax error near unexpected token `|'\n"));
	}
	while (str[i + n] == ';' && n < 2)
		n++;
	if (n == 2)
		return (printf("minishell: syntax error near unexpected token `;;'\n"));
	if (n == 1)
	{
		if (str[i + n] == '&')
			return (printf("minishell: syntax error near unexpected token `;&'\n"));
		else
			return (printf("minishell: syntax error near unexpected token `;'\n"));
	}
	while (str[i + n] == '>' && n < 2)
		n++;
	if (n == 2)
		return (printf("minishell: syntax error near unexpected token `>>'\n"));
	if (n == 1)
	{
		if (str[i + n] == '&' || str[i + n] == '|')
			return (printf("minishell: syntax error near unexpected token `>%c'\n", str[i + n]));
		else
			return (printf("minishell: syntax error near unexpected token `>'\n"));
	}
	return (0);
}

int	input_check(t_data *d)
{
	int	i;
	char	*str;
	char	*strs;

	i = 0;
	while (d->cmds[i])
	{
		// if (ft_strchr(strs[i], '<') && ft_strchr(strs[i], '>'))
		// {
		// 	if (ft_strchr(strs[i], '<') < ft_strchr(strs[i], '>'))
		// 	{
		// 		str = ft_strchr(strs[i], '<');
		// 		if (check_lessthan(str))
		// 		{
		// 			free(str);
		// 			return (1);
		// 		}
		// 	}
		// 	i++;
		// }
		strs = ft_strjoin(d->cmds[i], d->cmd[i].next_op);
		printf("next op = %s\n", d->cmd[i].next_op);
		if (ft_strchr(strs, '<'))
		{
			str = ft_strchr(strs, '<');
			if (check_lessthan(str))
			{
				free(strs);
				return (1);
			}i++;
		}
		else
			i++;
	}
	return (0);
}

// int	input_check(char **strs)
// {
// 	int	i;
// 	char	*str;

// 	i = 0;
// 	while (strs[i])
// 	{
// 		// if (ft_strchr(strs[i], '<') && ft_strchr(strs[i], '>'))
// 		// {
// 		// 	if (ft_strchr(strs[i], '<') < ft_strchr(strs[i], '>'))
// 		// 	{
// 		// 		str = ft_strchr(strs[i], '<');
// 		// 		if (check_lessthan(str))
// 		// 		{
// 		// 			free(str);
// 		// 			return (1);
// 		// 		}
// 		// 	}
// 		// 	i++;
// 		// }
// 		if (ft_strchr(strs[i], '<'))
// 		{
// 			str = ft_strchr(strs[i], '<');
// 			if (check_lessthan(str))
// 				return (1);
// 			i++;
// 		}
// 		else
// 			i++;
// 	}
// 	return (0);
// }
