
#include "../minishell.h"

int	check_lessthan(char *str)
{
	int	i;
	char	c;

	c = str[0];
	i = 1;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		while (cmd[i] && cmd[i] == '>')
	}
}

int	input_check(t_data *d, char **strs)
{
	int	i;
	char	*str;

	i = 0;
	while (strs[i])
	{
		if (ft_strchr(strs[i], '<') && ft_strchr(strs[i], '>'))
		{
			if (ft_strchr(strs[i], '<') < ft_strchr(strs[i], '>'))
			{
				str = ft_strchr(strs[i], '<');
				if ()
			}
		
		}
		else
			i++;
	}
}
