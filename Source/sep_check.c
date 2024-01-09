
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

int	check_pipe(char *sep)
{
	int	i;

	if (!ft_strncmp(sep, "|", ft_strlen(sep)))
		return (0);
	if (!ft_strncmp(sep, "||", ft_strlen(sep)))
		return (0);
	i = 1;
	while (sep[i] == '|')
		i++;
	if (i == 2)
		return (printf("error msg to implement\n"));
	if (i > 2)
		return (printf("error msg to implement\n"));
	return (1);
}

int	check_esp(char *sep)
{
	int	i;

	if (ft_strlen(sep) < 3)
	{
		if (!ft_strncmp(sep, "&", ft_strlen(sep)))
			return (0);
		if (!ft_strncmp(sep, "&&", 2))
			return (0);
	}
	i = 1;
	while (sep[i] == '&')
		i++;
	if (i == 2)
		return (printf("error msg to implement\n"));
	if (i > 2)
		return (printf("error msg to implement\n"));
	return (1);
}

int	sep_check(char **seps)
{
	int	i;
	int	len;

	i = 0;
	if (!seps)
		return (0);
	while (seps[i])
	{
		len = ft_strlen(seps[i]);
		if (!ft_strncmp(seps[i], "|", len) || !ft_strncmp(seps[i], "||", len))
			i++;
		else if (!ft_strncmp(seps[i], "&&", len))
			i++;
		else
			return (1); //err msg a implement
	}
	return (0);
}