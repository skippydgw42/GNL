/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegraeu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:24:17 by mdegraeu          #+#    #+#             */
/*   Updated: 2021/11/21 15:35:06 by mdegraeu         ###   ########lyon.fr   */
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

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*output;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	output = malloc(sizeof(char) * (len + 1));
	if (!output)
		return (NULL);
	while (s1[i])
	{
		output[i] = s1[i];
		i++;
	}
	while (s2[j] || s2[j] == '\n')
		output[i++] = s2[j++];
	output[i] = '\0';
	return (output);
}

char	*ft_strndup(char *str, int n)
{
	int		i;
	char	*output;

	i = 0;
	output = malloc(sizeof(char) * (n + 1));
	if (!output)
		return (NULL);
	while (str[i] && i < n)
	{
		output[i] = str[i];
		i++;
	}
	output[i] = '\0';
	return (output);
}

char	*ft_check(char *str)
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
/*
char	*ft_dispatch(char *str, char buf[BUFFER_SIZE + 1])
{
	char	*temp;
	char	*output;

	if (ft_strchr(str, '\n'))
	{
		temp = str;
		output = ft_strndup(temp, ft_strlen(temp) - ft_strlen(ft_strchr(temp, '\n')) + 1);
		str = ft_strndup(ft_strchr(temp, '\n') + 1, ft_strlen(ft_strchr(temp, '\n')));
		free(temp);
		return (output);
	}
	else
	{
		temp = str;
		str = ft_strjoin(temp, buf);
		free(temp);
	}
	return (str);
}
*/
/*
char	*get_next_line(int fd)
{
	int				ret;
	char			buf[BUFFER_SIZE + 1];
	static char		*str = NULL;
	//char			*output;

	if (fd <= 0 || fd > 1024 || BUFFER_SIZE < 1)
		return (NULL);
	ret = 1;
	while (ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		buf[ret] = '\0';
		if (ret < 1 && !str)
		{
			free(str);
			return (NULL);
		}
		str = ft_check(str);
		if (!str)
			str = ft_strndup(buf, ft_strlen(buf));
		str = ft_dispatch(str, buf);
		if (ft_strchr(str, '\n'))// || ret == 0)
			return (str);
	}
	return (str);
}
*/
char	*get_next_line(int fd)
{
	int			ret;
	char		buf[BUFFER_SIZE + 1];
	char		*str;
	char		*temp;
	static char	*stat_str = NULL;

	if (fd < 1 || BUFFER_SIZE < 1)
		return (NULL);
	ret = 1;
	str = malloc(sizeof(char) * 1);
	str[0] = '\0';
	while (ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret < 1)
			return (NULL);
		buf[ret] = '\0';
		if (!ft_strchr(buf,'\n'))
		{
			if (stat_str)
			{
				str = ft_strjoin(stat_str, buf);
				free(stat_str);
			}
			else
				str = ft_strjoin(str, buf);
			printf("str : %s\n", str);
		}
		if (ft_strchr(buf, '\n'))
		{
			temp = ft_strjoin(str, buf);
			stat_str = ft_strndup(ft_strchr(buf, '\n') + 1, ft_strlen(buf));
			str = ft_strndup(temp, ft_strlen(temp) - ft_strlen(stat_str));
			free (temp);
			return (str);
		}
	}
	return (stat_str);
}

int	main()
{
	int		fd;

	fd = open("file_test", O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
//	printf("%s", get_next_line(fd));
//	printf("%s", get_next_line(fd));
//	printf("%s", get_next_line(fd));
}

