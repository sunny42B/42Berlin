/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_func_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:30:40 by sung-hle          #+#    #+#             */
/*   Updated: 2023/10/18 19:57:49 by sung-hle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	set_image_depth(mlx_image_t *image, int z)
{
	size_t	i;

	i = 0;
	while (i < image->count)
	{
		image->instances[i].z = z;
		i++;
	}
}

/*
UP 1
DOWN 2
LEFT 3
RIGHT 4
*/

int	checker_wall(t_vars *vars, mlx_image_t *pic, int i, int direction)
{
	int		xs;
	int		ys;

	xs = pic->instances[i].x / IMGSIZE;
	ys = pic->instances[i].y / IMGSIZE;
	if (direction == 1 && vars->map[ys - 1][xs] == '1')
		return (1);
	if (direction == 2 && vars->map[ys + 1][xs] == '1')
		return (1);
	if (direction == 3 && vars->map[ys][xs - 1] == '1')
		return (1);
	if (direction == 4 && vars->map[ys][xs + 1] == '1')
		return (1);
	if (pic == vars->player && vars->win_lose_flag == 0)
		ft_printf("steps %d\n", ++vars->steps);
	return (0);
}

int	checker_collectible(t_vars *vars)
{
	int	xs;
	int	ys;

	xs = vars->player->instances[0].x / IMGSIZE;
	ys = vars->player->instances[0].y / IMGSIZE;
	if (vars->map[ys][xs] == 'C')
	{
		vars->coll->instances[which_instance(vars)].enabled = false;
		vars->map[ys][xs] = '0';
		vars->c_ctr--;
		if (vars->c_ctr == 0)
		{
			vars->gameexit->instances[0].enabled = false;
			vars->open->instances[0].enabled = true;
		}
		return (1);
	}
	return (0);
}
