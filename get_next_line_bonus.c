/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegraeu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:32:42 by mdegraeu          #+#    #+#             */
/*   Updated: 2021/11/24 13:44:11 by mdegraeu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_strcdup(char *str, char c)
{
	int		i;
	size_t	n;
	char	*output;

	i = 0;
	n = ft_strlen(str);
	if (n == 0)
		return (NULL);
	output = malloc(sizeof(char) * (n + 1));
	if (!output)
		return (NULL);
	while (str[i])
	{
		if (str[i] == c)
		{
			output[i] = str[i];
			i++;
			break ;
		}
		output[i] = str[i];
		i++;
	}
	output[i] = '\0';
	return (output);
}

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_calloc(1, 1));
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	if (start < ft_strlen(s))
	{
		str = ft_calloc((len + 1), sizeof(char));
		if (!str)
			return (NULL);
	}
	while (i < len)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}

static char	*ft_return_line(char **str)
{
	char	*newline;
	char	*nextline;
	char	*to_free;

	if (ft_strlen(*str) == 0)
	{
		free(*str);
		return (NULL);
	}
	newline = ft_strcdup(*str, '\n');
	nextline = ft_strchr(*str, '\n');
	to_free = *str;
	*str = ft_substr(*str, nextline - *str + 1, ft_strlen(*str));
	free(to_free);
	return (newline);
}

char	*get_next_line(int fd)
{
	int			ret;
	char		buf[BUFFER_SIZE + 1];
	static char	*str[1024];
	char		*to_free;

	if (fd < 0)
		return (NULL);
	ret = read(fd, buf, BUFFER_SIZE);
	if (ret < 0 || (ret == 0 && !str[fd]))
		return (NULL);
	while (ret > 0)
	{
		buf[ret] = '\0';
		to_free = str[fd];
		str[fd] = ft_strjoin(str[fd], buf);
		if (to_free)
			free(to_free);
		if (ft_strchr(str[fd], '\n'))
			return (ft_return_line(&str[fd]));
		ret = read(fd, buf, BUFFER_SIZE);
	}
	return (ft_return_line(&str[fd]));
}
/*
int	main()
{
	int		fd1;
	int		fd2;

	fd1 = open("file_test", O_RDONLY);
	fd2 = open("file_test_2", O_RDONLY);
	printf("%s", get_next_line(fd1));
	printf("%s", get_next_line(fd2));
	printf("%s", get_next_line(fd1));
	printf("%s", get_next_line(fd2));
	printf("%s", get_next_line(fd1));
	printf("%s", get_next_line(fd2));
	printf("%s", get_next_line(fd1));
	printf("%s", get_next_line(fd2));
}
*/
