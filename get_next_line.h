/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegraeu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 12:02:47 by mdegraeu          #+#    #+#             */
/*   Updated: 2021/11/22 14:02:46 by mdegraeu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
# include <string.h>

//==========GET_UTILS.c===========//
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *str, int c);
char	*ft_strjoin(char *s1, char *s2);

//===========GET_NEXT.c==========//
char	*ft_strcdup(char *str, char c);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_check(char *str);
char	*ft_return_line(char **str);
char	*get_next_line(int fd);

#endif
