/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegraeu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 12:03:19 by mdegraeu          #+#    #+#             */
/*   Updated: 2021/11/12 12:27:03 by mdegraeu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] || str[i] == '\n')
		i++;
	return (i);
}

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&str[i]);
	return (NULL);
}

char	*ft_check_reset(char *str)
{
	static int	i;

	if (i > 0)
		return (str);
	str = malloc(sizeof(char) * 1);
	if (!str)
		return (NULL);
	str[0] = '\0';
	i++;
	return (str);
}

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE + 1];
	static char	*str;
	char		*temp;
	size_t		index;
	size_t		ret;

	if (!fd)
		return (NULL);
	index = 0;
	ret = -1;
	str = ft_check_reset(str);
	while (ret != 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		buf[BUFFER_SIZE] = '\0';
		if (ft_strchr(buf, '\n'))
		{
			index = ft_strlen(buf) - ft_strlen(ft_strchr(buf, '\n'));
			str = ft_strjoin(str, ft_substr(buf, 0, index + 1));
			temp = str;
			str = ft_substr(buf, index + 1, ft_strlen(ft_strchr(buf, '\n'))); 
			return (temp);
		}
		else
			str = ft_strjoin(str, buf);
	}
	return (str);
}

int	main()
{
	int		fd;
	int	i;

	i = 0;
	fd = open("file_test", O_RDONLY);
	while (i < 4)
	{
		printf("%s\n", get_next_line(fd));
		i++;
	}
}

