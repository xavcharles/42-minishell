
#include "minishell.h"


int check_redir(char *sep)
{
	if (ft_strlen(sep) < 3)
	{
		if (!ft_strncmp(sep, "<", ft_strlen(sep)))
			return (0);
		if (!ft_strncmp(sep, ">", ft_strlen(sep)))
			return (0);
		if (!ft_strncmp(sep, ">>", 2))
			return (0);
		if (!ft_strncmp(sep, "<<", 2))
			return (0);
		if (!ft_strncmp(sep, "<>", 2))
			return (0);
	}
	while (sep[i])
	{
		if (sep([i]) == '>')
	}

}

int	check_pipe(char *sep)
{
	int	i;

	if (!ft_strncmp(sep, "|", ft_strlen(sep)))
		return (0);
	if (!ft_strncmp(sep, "||", ft_strlen(sep)))
		return (0);
	i = 1;
	while (sep[i] == "|")
		i++;
	if (i = 2)
		return (printf("error msg to implement\n"));
	if (i > 2)
		return (printf("error msg to implement\n"));
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
	while (sep[i] == "&")
		i++;
	if (i = 1)
		return (printf("error msg to implement\n"));
	if (i > 1)
		return (printf("error msg to implement\n"));
}

int	sep_check(char **seps)
{
	char **strs;

	strs = seps;
	while (*strs)
	{

	}
}