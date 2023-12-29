
#include "../minishell.h"


// int check_redir(char *sep)
// {
// 	if (ft_strlen(sep) < 3)
// 	{
// 		if (!ft_strncmp(sep, "<", ft_strlen(sep)))
// 			return (0);
// 		if (!ft_strncmp(sep, ">", ft_strlen(sep)))
// 			return (0);
// 		if (!ft_strncmp(sep, ">>", 2))
// 			return (0);
// 		if (!ft_strncmp(sep, "<<", 2))
// 			return (0);
// 		if (!ft_strncmp(sep, "<>", 2))
// 			return (0);
// 	}
// 	while (sep[i])
// 	{
// 		if (sep([i]) == '>')
// 	}

// }

int	check_pipe(char *str, int *i)
{
	int	n;

	*i = 0;
	n = 0;
	while (str[*i] && str[*i] == '|' && *i < 4)
		(*i)++;
	if (*i == 4)
		return (printf("minishell: syntax error near unexpected token `||'\n"));
	if (*i == 3)
		return (printf("minishell: syntax error near unexpected token `|'\n"));
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
	while (str[*i + n] == '&' && n < 2)
		n++;
	if (n == 2)
		return (printf("minishell: syntax error near unexpected token `&&'\n"));
	if (n == 1)
		return (printf("minishell: syntax error near unexpected token `&'\n"));
	while (str[*i + n] == '|' && n < 2)
		n++;
	if (n == 2)
		return (printf("minishell: syntax error near unexpected token `||'\n"));
	if (n == 1 && str[*i + n] == '&')
		return (printf("minishell: syntax error near unexpected token `|&'\n"));
	if (n == 1)
		return (printf("minishell: syntax error near unexpected token `|'\n"));
	while (str[*i + n] == ';' && n < 2)
		n++;
	if (n == 2)
		return (printf("minishell: syntax error near unexpected token `;;'\n"));
	if (n == 1 && str[*i + n] == '&')
		return (printf("minishell: syntax error near unexpected token `;&'\n"));
	if (n == 1)
		return (printf("minishell: syntax error near unexpected token `;'\n"));
	return (0);
}

int	check_esp(char *str, int *i)
{
	int	n;

	*i = 0;
	n = 0;
	while (str[*i] && str[*i] == '&' && *i < 4)
		(*i)++;
	if (*i == 4)
		return (printf("minishell: syntax error near unexpected token `&&'\n"));
	if (*i == 3)
		return (printf("minishell: syntax error near unexpected token `&'\n"));
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
	while (str[*i + n] == '&' && n < 2)
		n++;
	if (n == 2)
		return (printf("minishell: syntax error near unexpected token `&&'\n"));
	if (n == 1)
		return (printf("minishell: syntax error near unexpected token `&'\n"));
	while (str[*i + n] == '|' && n < 2)
		n++;
	if (n == 2)
		return (printf("minishell: syntax error near unexpected token `||'\n"));
	if (n == 1 && str[*i + n] == '&')
		return (printf("minishell: syntax error near unexpected token `|&'\n"));
	if (n == 1)
		return (printf("minishell: syntax error near unexpected token `|'\n"));
	while (str[*i + n] == ';' && n < 2)
		n++;
	if (n == 2)
		return (printf("minishell: syntax error near unexpected token `;;'\n"));
	if (n == 1 && str[*i + n] == '&')
		return (printf("minishell: syntax error near unexpected token `;&'\n"));
	if (n == 1)
		return (printf("minishell: syntax error near unexpected token `;'\n"));
	return (0);
}


// int	sep_check(char **seps)
// {
// 	int	i;
// 	int	len;

// 	i = 0;
// 	if (!seps)
// 		return (0);
// 	while (seps[i])
// 	{
// 		len = ft_strlen(seps[i]);
// 		if (!ft_strncmp(seps[i], "|", len) || !ft_strncmp(seps[i], "||", len))
// 			i++;
// 		else if (!ft_strncmp(seps[i], "&&", len))
// 			i++;
// 		else
// 			return (1); //err msg a implement
// 	}
// 	return (0);
// }