/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:49:17 by sung-hle          #+#    #+#             */
/*   Updated: 2023/09/05 11:27:51 by sung-hle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	line_check(t_cub *cub, char *joined)
{
	size_t	i;
	char	*found;

	i = 0;
	found = ft_strnstr(joined, cub->config->map[0], ft_strlen(joined));
	while (found[i] != '\0' && i < ft_strlen(found) - 1)
	{
		if (found[i] == '\n' && found[i + 1] == '\n')
			return (printf("error, empty line in map found\n"), 1);
		i++;
	}
	if (found[ft_strlen(found) - 1] == '\n')
		return (printf("error, empty line at the end of map found\n"), 1);
	return (0);
}

int	valid_chars(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (!(map[i][j] == '1' || map[i][j] == '0' || map[i][j] == 'N'\
				|| map[i][j] == 'E' || map[i][j] == 'S' || map[i][j] == 'W'\
				|| map[i][j] == ' '))
				return (printf("error, invalid char found\n"), 1);
			j++;
		}
		i++;
	}
	return (0);
}

int	f_fill_out(char **tab, t_point pt)
{
	return (tab[pt.x][pt.y] == '0' || tab[pt.x][pt.y] == 'N' || \
	tab[pt.x][pt.y] == 'S' || tab[pt.x][pt.y] == 'W' || \
	tab[pt.x][pt.y] == 'E');
}

void	f_fill(char **tab, t_cub *cub, int *flag, t_point pt)
{
	if (*flag == 1)
		return ;
	if (pt.flag == 0 && (pt.y < 0 || pt.x < 0 || pt.x >= cub->config->map_h || \
		pt.y >= (int)ft_strlen(tab[pt.x]) || tab[pt.x][pt.y] == ' '))
	{
		*flag = 1;
		return ;
	}
	if (pt.x < 0 || pt.y < 0 || pt.x >= cub->config->map_h || \
		pt.y >= (int)ft_strlen(tab[pt.x]) || tab[pt.x][pt.y] == '1')
		return ;
	if (f_fill_out(tab, pt))
		pt.flag = 0;
	else
		pt.flag = 1;
	tab[pt.x][pt.y] = '1';
	pt.x -= 1;
	f_fill(tab, cub, flag, pt);
	pt.x += 2;
	f_fill(tab, cub, flag, pt);
	pt.y -= 1;
	pt.x -= 1;
	f_fill(tab, cub, flag, pt);
	pt.y += 2;
	f_fill(tab, cub, flag, pt);
}

void	flood_fill(char **tab, t_cub *cub, int *flag, t_point begin)
{
	f_fill(tab, cub, flag, begin);
}
