
#include "../minishell.h"

int	check_first(char *input)
{
	int	i;

	i = 0;
	if (input[0] == '|')
	{
		while (input[i] && input[i] == '|' && i < 2)
			i++;
		if (i == 2)
			return (printf("minishell: syntax error near unexpected token `||'\n"));
		if (i == 1 && input[i] == '&')
			return (printf("minishell: syntax error near unexpected token `|&'\n"));
		else
			return (printf("minishell: syntax error near unexpected token `|'\n"));
	}
	else if (input[0] == '&')
	{
		while (input[i] && input[i] == '&' && i < 2)
			i++;
		if (i == 2)
			return (printf("minishell: syntax error near unexpected token `&&'\n"));
		else
			return (printf("minishell: syntax error near unexpected token `&'\n"));
	}
	return (0);
}

int	check_firstbis(char *input)
{
	int	i;

	i = 0;
	if (input[0] == ';')
	{
		while (input[i] && input[i] == ';' && i < 2)
			i++;
		if (i == 2)
			return (printf("minishell: syntax error near unexpected token `;;'\n"));
		if (i == 1 && input[i] == '&')
			return (printf("minishell: syntax error near unexpected token `;&'\n"));
		else
			return (printf("minishell: syntax error near unexpected token `;'\n"));
	}
	return (0);
}

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
