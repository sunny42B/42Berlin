/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:48:53 by sung-hle          #+#    #+#             */
/*   Updated: 2023/09/05 11:27:51 by sung-hle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_start_pos(char **dup, t_point *start)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	k = 0;
	while (dup[++i] != NULL)
	{
		j = -1;
		while (dup[i][++j] != '\0')
		{
			if ((dup[i][j] == 'N' || dup[i][j] == 'W'\
				|| dup[i][j] == 'E' || dup[i][j] == 'S'))
			{
				if (++k > 1)
					return (printf("error, more than one player\n"), 1);
				start->x = i;
				start->y = j;
				start->flag = dup[i][j];
			}
		}
	}
	if (start->x != -1 && start->y != -1)
		return (0);
	return (printf("error, no start pos\n"), 1);
}

int	check_surroundings(char **map, int i, int j)
{
	if (map[++i][j] != '1')
		return (1);
	--i;
	if (map[--i][j] != '1')
		return (1);
	++i;
	if (map[i][++j] != '1')
		return (1);
	--j;
	if (map[i][--j] != '1')
		return (1);
	return (0);
}

int	check_zeros(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == '0')
				if (check_surroundings(map, i, j))
					return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	wall_check(t_cub *cub, char **map)
{
	char	**tmp;
	int		i;
	int		flag;
	t_point	start;

	i = 0;
	flag = 0;
	start.x = -1;
	start.y = -1;
	tmp = dup_map(cub, map);
	if (!tmp)
		return (printf("error when dup malloc\n"), 1);
	if (get_start_pos(tmp, &start))
		return (ft_free(tmp), 1);
	start.flag = 0;
	flood_fill(tmp, cub, &flag, start);
	if (flag == 1)
		return (ft_free(tmp), printf("error with map\n"), 1);
	ft_free(tmp);
	return (0);
}
