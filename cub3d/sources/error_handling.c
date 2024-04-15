/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:50:56 by sung-hle          #+#    #+#             */
/*   Updated: 2023/09/04 20:14:54 by sung-hle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	int		len;
	char	*dup;

	len = ft_strlen(str);
	dup = ft_strnstr(&(str[len - 4]), ".cub", 4);
	return (dup);
}

char	*read_file(char *argv, int *i)
{
	int		file;
	char	*joined;
	char	*r;

	r = NULL;
	file = open(argv, O_RDONLY);
	if (file == -1)
		return (NULL);
	joined = ft_calloc(1, 1);
	while (1)
	{
		r = get_next_line(file);
		if (!r)
			break ;
		joined = join_and_free(joined, r);
		if (!joined)
			return (NULL);
		(*i)++;
	}
	return (joined);
}

int	is_map(char chr)
{
	return (chr == '0' || chr == '1');
}

int	is_player(char chr)
{
	return (chr == 'N' || chr == 'S' || chr == 'E' || chr == 'W');
}
