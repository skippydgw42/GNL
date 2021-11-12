/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegraeu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:24:17 by mdegraeu          #+#    #+#             */
/*   Updated: 2021/11/12 16:31:12 by mdegraeu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"



char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE + 1];
	static char	*str;
	char		*temp;
	int			ret;
	size_t		index;
	
	if (fd < 0)
		return (NULL);
	ret = 1;
	while (ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		buf[BUFFER_SIZE] = '\0';
		if (ft_strchr(buf, '\n'))
		{

		}
		else
		{
			temp = str;
			str = ft_strjoin(str, buf);
			free(temp);
		}
	}
	return (NULL);
}
