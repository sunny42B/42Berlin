/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:50:56 by sung-hle          #+#    #+#             */
/*   Updated: 2023/05/29 16:57:36 by sung-hle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

char	*join_and_free(char *a, char *b)
{
	char	*joined;
	size_t	len;
	size_t	jsize;
	size_t	i;

	i = 0;
	len = ft_gnllen(a) + ft_gnllen(b);
	joined = (char *)ft_calloc_gnl(len + 1);
	if (joined == NULL)
		return (joined);
	ft_gnllcpy(joined, a, ft_gnllen(a) + 1);
	jsize = ft_gnllen(joined);
	while (jsize + i < len && b[i] != '\0')
	{
		joined[jsize + i] = b[i];
		i++;
	}
	joined[jsize + i] = '\0';
	free(a);
	free(b);
	return (joined);
}

char	*check_suffix(char *str)
{
	int	len;

	len = ft_strlen(str);
	return (ft_strnstr(&(str[len - 4]), ".ber", 4));
}

char	*read_file(char *argv, int *i)
{
	int		file;
	char	*joined;
	char	*r;

	r = NULL;
	joined = ft_calloc(1, 1);
	file = open(argv, O_RDONLY);
	if (file == -1)
		return (NULL);
	while (1)
	{
		r = get_next_line(file);
		if (!r)
			break ;
		if (ft_strlen(r) == 1)
			return (NULL);
		joined = join_and_free(joined, r);
		(*i)++;
	}
	if (joined[0] == '\n' || check_lines(joined))
	{
		free(joined);
		return (NULL);
	}
	return (joined);
}

void	ft_free(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

int	ft_error_sl(char *s)
{
	ft_putstr_fd(s, 1);
	return (1);
}
