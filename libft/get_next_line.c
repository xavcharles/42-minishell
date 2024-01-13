/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacharle <xacharle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:51:43 by xacharle          #+#    #+#             */
/*   Updated: 2023/06/25 16:30:00 by xacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*gnl_strjoin(char *s1, char *s2)
{
	size_t	size;
	char	*str;

	size = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	str[0] = 0;
	if (s1)
		ft_strlcat(str, s1, size + 1);
	if (s2)
		ft_strlcat(str, s2, size + 1);
	if (s1)
		free(s1);
	return (str);
}

char	*ft_remember(char *statik)
{
	char	*cpy;
	int		nlen;

	if (is_line(statik, ft_strlen(statik)))
	{
		nlen = ft_len(statik, '\n');
		cpy = ft_strdup(statik + nlen + 1);
		free(statik);
		if (cpy[0] == 0)
		{
			free(cpy);
			return (NULL);
		}
		return (cpy);
	}
	free(statik);
	return (NULL);
}

char	*mod_if_line(char *statik)
{
	char	*line;
	char	*cpy;
	int		len;

	len = ft_strlen(statik);
	if (!statik[0])
		return (NULL);
	if (is_line(statik, len))
	{
		cpy = ft_strdup(statik);
		ft_bzero(cpy + ft_len(cpy, '\n') + 1, len - ft_len(cpy, '\n'));
		line = ft_strdup(cpy);
		free(cpy);
		return (line);
	}
	line = ft_strdup(statik);
	return (line);
}

char	*read_n_write(int fd, char *statik)
{
	char	*buf;
	int		j;
	int		l;

	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	j = 1;
	l = j;
	while (!is_line(statik, l) && j != 0)
	{
		j = read(fd, buf, BUFFER_SIZE);
		if (j < 0)
		{
			free(buf);
			return (NULL);
		}
		buf[j] = 0;
		statik = gnl_strjoin(statik, buf);
		ft_bzero(buf, ft_strlen(buf));
		l = ft_strlen(statik);
	}
	free(buf);
	return (statik);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;

	if (fd < 0)
		return (NULL);
	buffer[fd] = read_n_write(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = mod_if_line(buffer[fd]);
	buffer[fd] = ft_remember(buffer[fd]);
	return (line);
}

// int	main()
// {
// 	char	*test;
// 	int	fd1;
// // 	int	fd2;

// 	fd1 = open("test", O_RDWR);
// 	test = get_next_line(fd1);
// 	while (test)
// 	{
// 		printf("- %s", test);
// 		free(test);
// 		test = get_next_line(fd1);

// 	}
// 	free(test);
// // 	fd2 = open("file2", O_RDWR);
// // 	test = get_next_line(fd2);
// // 	printf("** %s **\n", test);
// // 	test = get_next_line(fd1);
// // 	printf("** %s **\n", test);
// // 	free(test);
// // 	fd2 = open("file2", O_RDWR);
// // 	test = get_next_line(fd2);
// // 	printf("** %s **\n", test);
// 	return (0);
// }
