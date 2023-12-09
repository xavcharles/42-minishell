
#include "../minishell.h"

char	*join_w_space(char *s1, char *s2)
{
	size_t	size;
	char	*str;

	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	str[0] = 0;
	if (s1)
	{
		ft_strlcat(str, s1, size + 1);
		str[ft_strlen(s1) + 1] = 0;
		str[ft_strlen(s1)] = ' ';
	}
	if (s2)
		ft_strlcat(str, s2, size + 1);
	if (s1)
		free(s1);
	return (str);
}

char	*join_w_tab(char *s1, char *s2)
{
	size_t	size;
	char	*str;

	size = ft_strlen(s1) + ft_strlen(s2) + 2;
	str = malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	str[0] = 0;
	if (s1)
	{
		ft_strlcat(str, s1, size + 1);
		str[ft_strlen(s1) + 1] = 0;
		str[ft_strlen(s1)] = ' ';
	}
	if (s2)
		ft_strlcat(str, s2, size + 1);
	str[size] = 0;
	str[size - 1] = '\t';
	if (s1)
		free(s1);
	return (str);
}
