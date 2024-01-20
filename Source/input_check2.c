
#include "../minishell.h"

int check_parenth(char *str, int *i)
{
    *i = 0;
	if (str[*i] == ')')
		return (printf("minishell: syntax error near unexpected token `)'\n"), 1);
	else if (str[*i] == '(')
		return (printf("minishell: syntax error near unexpected token `('\n"), 1);
	return (0);
}

int	check_braces(char *str, int *i)
{
	*i = 0;
	if (str[*i] == ']')
		return (printf("minishell: syntax error near unexpected token `]'\n"), 1);
	else if (str[*i] == '[')
		return (printf("minishell: syntax error near unexpected token `['\n"), 1);
	return (0);
}