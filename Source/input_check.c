
#include "../minishell.h"

int	check_morethan(char *str, int *i)
{
	// int	i;
	int	n;

	*i = 0;
	n = 0;
	while (str[*i] && str[*i] == '>' && *i < 2)
		(*i)++;
	if (*i == 1 && str[*i] == '&')
		(*i)++;
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
	if (!str[*i])
		return (printf("minishell: syntax error near unexpected token `newline'\n"));
	// if (!is_charset(str[*i], "&|;><") && str[1] == '&')
	// 	return (printf("bash: ambiguous redirect\n"));
	while (str[*i + n] == '<' && n < 3)
		n++;
	if (n == 3)
		return (printf("minishell: syntax error near unexpected token `<<<'\n"));
	if (n == 2)
		return (printf("minishell: syntax error near unexpected token `<<'\n"));
	if (n == 1)
	{
		if (!is_charset(str[*i + n], "&>"))
			return (printf("minishell: syntax error near unexpected token `<'\n"));
		else
			return (printf("minishell: syntax error near unexpected token `<%c'\n", str[*i + n]));
	}
	while (str[*i + n] == '&' && n < 2)
		n++;
	if (n == 2)
		return (printf("minishell: syntax error near unexpected token `&&'\n"));
	if (n == 1)
	{
		if (str[*i + n] == '>' && str[*i + n + 1] == '>')
			return (printf("minishell: syntax error near unexpected token `&>>'\n"));
		else if (str[*i + n] == '>')
			return (printf("minishell: syntax error near unexpected token `&>'\n"));
		else
			return (printf("minishell: syntax error near unexpected token `&'\n"));
	}
	while (str[*i + n] == '|' && n < 2)
		n++;
	if (n == 2)
		return (printf("minishell: syntax error near unexpected token `||'\n"));
	if (n == 1)
	{
		if (str[*i + n] == '&')
			return (printf("minishell: syntax error near unexpected token `|&'\n"));
		else
			return (printf("minishell: syntax error near unexpected token `|'\n"));
	}
	while (str[*i + n] == ';' && n < 2)
		n++;
	if (n == 2)
		return (printf("minishell: syntax error near unexpected token `;;'\n"));
	if (n == 1)
	{
		if (str[*i + n] == '&')
			return (printf("minishell: syntax error near unexpected token `;&'\n"));
		else
			return (printf("minishell: syntax error near unexpected token `;'\n"));
	}
	while (str[*i + n] == '>' && n < 2)
		n++;
	if (n == 2)
		return (printf("minishell: syntax error near unexpected token `>>'\n"));
	if (n == 1)
	{
		if (str[*i + n] == '&' || str[*i + n] == '|')
			return (printf("minishell: syntax error near unexpected token `>%c'\n", str[*i + n]));
		else
			return (printf("minishell: syntax error near unexpected token `>'\n"));
	}
	while (is_charset(str[*i], "&|><;"))
		(*i)++;
	return (0);
}

int	check_lessthan(char *str, int *i)
{
	// int	i;
	int	n;

	*i = 0;
	n = 0;
	while (str[*i] && str[*i] == '<' && *i < 3)
		(*i)++;
	if (*i == 1 && str[*i] == '&')
		(*i)++;
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
	if (!str[*i])
		return (printf("minishell: syntax error near unexpected token `newline'\n"));
	if (!is_charset(str[*i], "&|;><") && str[1] == '&')
		return (printf("bash: ambiguous redirect\n"));
	while (str[*i + n] == '<' && n < 3)
		n++;
	if (n == 3)
		return (printf("minishell: syntax error near unexpected token `<<<'\n"));
	if (n == 2)
		return (printf("minishell: syntax error near unexpected token `<<'\n"));
	if (n == 1)
	{
		if (!is_charset(str[*i + n], "&>"))
			return (printf("minishell: syntax error near unexpected token `<'\n"));
		else
			return (printf("minishell: syntax error near unexpected token `<%c'\n", str[*i + n]));
	}
	while (str[*i + n] == '&' && n < 2)
		n++;
	if (n == 2)
		return (printf("minishell: syntax error near unexpected token `&&'\n"));
	if (n == 1)
	{
		if (str[*i + n] == '>' && str[*i + n + 1] == '>')
			return (printf("minishell: syntax error near unexpected token `&>>'\n"));
		else if (str[*i + n] == '>')
			return (printf("minishell: syntax error near unexpected token `&>'\n"));
		else
			return (printf("minishell: syntax error near unexpected token `&'\n"));
	}
	while (str[*i + n] == '|' && n < 2)
		n++;
	if (n == 2)
		return (printf("minishell: syntax error near unexpected token `||'\n"));
	if (n == 1)
	{
		if (str[*i + n] == '&')
			return (printf("minishell: syntax error near unexpected token `|&'\n"));
		else
			return (printf("minishell: syntax error near unexpected token `|'\n"));
	}
	while (str[*i + n] == ';' && n < 2)
		n++;
	if (n == 2)
		return (printf("minishell: syntax error near unexpected token `;;'\n"));
	if (n == 1)
	{
		if (str[*i + n] == '&')
			return (printf("minishell: syntax error near unexpected token `;&'\n"));
		else
			return (printf("minishell: syntax error near unexpected token `;'\n"));
	}
	while (str[*i + n] == '>' && n < 2)
		n++;
	if (n == 2)
		return (printf("minishell: syntax error near unexpected token `>>'\n"));
	if (n == 1)
	{
		if (str[*i + n] == '&' || str[*i + n] == '|')
			return (printf("minishell: syntax error near unexpected token `>%c'\n", str[*i + n]));
		else
			return (printf("minishell: syntax error near unexpected token `>'\n"));
	}
	while (is_charset(str[*i], "&|><;"))
		(*i)++;
	return (0);
}

int	input_check(t_data *d)
{
	int	i;
	char	*str;

	i = 0;
	str = d->input;
	while (*str)
	{
		if (!is_charset(*str, "&|><"))
			str++;
		else
		{
			if (*str == '<')
			{
				i = 0;
				str = ft_strchr(str, '<');
				if (check_lessthan(str, &i))
				{
					return (1);
				}
				str += i;
			}
			else if (*str == '>')
			{
				i = 0;
				str = ft_strchr(str, '>');
				if (check_morethan(str, &i))
				{
					return (1);
				}
				str += i;
			}
		}
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
