/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:54:59 by fhassoun          #+#    #+#             */
/*   Updated: 2023/04/11 09:50:33 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//delete these headers before evaluation
#include <fcntl.h>
#include <stdio.h>
//delete these headers before evaluation

char	*str_newline(char *str)
{
	int		i;
	char	*buf;

	buf = ft_gnl_strdup(str);
	i = 0;
	while (buf[i] != '\0')
	{
		if (buf[i] == '\n')
		{
			buf[i + 1] = '\0';
			return (buf);
		}
		i++;
	}
	if (!buf[0])
	{
		free(buf);
		return (NULL);
	}
	return (buf);
}

char	*get_string(char *str, int fd)
{
	char	*buf1;
	int		index;

	index = 1;
	buf1 = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf1)
		return (NULL);
	while (!ft_strchr(str, '\n') && index != 0)
	{
		index = read(fd, buf1, BUFFER_SIZE);
		if (index == -1)
		{
			free(str);
			free(buf1);
			return (NULL);
		}
		buf1[index] = '\0';
		str = ft_gnl_strjoin(str, buf1);
	}
	free(buf1);
	return (str);
}

char	*prepare_str(char *str)
{
	int		i;
	int		j;
	char	*buf2;

	i = 0;
	j = 0;
	buf2 = malloc(ft_strlen(str) + (sizeof(char) + 2));
	if (!buf2)
		return (NULL);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	while (str[i] != '\0')
		buf2[j++] = str[i++];
	buf2[j] = '\0';
	free(str);
	if (!buf2[0])
	{
		free(buf2);
		return (NULL);
	}
	return (buf2);
}

char	*get_next_line(int fd)
{
	static char	*str[1024];
	char		*newline;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (!str[fd])
	{
		str[fd] = (char *)malloc(sizeof(char) * 1);
		if (!str[fd])
			return (NULL);
		str[fd][0] = '\0';
	}
	str[fd] = get_string(str[fd], fd);
	if (!str[fd])
		return (NULL);
	newline = NULL;
	newline = str_newline(str[fd]);
	str[fd] = prepare_str(str[fd]);
	return (newline);
}
/*
int	main(void)
{
	int		fd;
	int		fd2;
	int		i;
	char	*text;
	char	*text2;

	fd = open("test.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	i = 0;
	while (i < 10)
	{
		text = get_next_line(fd);
		printf("%s/n", text);
		text = get_next_line(fd2);
		printf("%s/n", text2);
		i++;
	}
	close(fd);
	return (0);
}
*/