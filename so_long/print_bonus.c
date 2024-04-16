/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:55:52 by sung-hle          #+#    #+#             */
/*   Updated: 2023/05/24 16:56:05 by sung-hle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	print_ground(t_vars *vars)
{
	int	xs;
	int	ys;

	ys = -1;
	while (++ys < vars->size_y)
	{
		xs = -1;
		while (++xs < vars->size_x)
			if (mlx_image_to_window(vars->mlx, vars->ground, \
				xs * IMGSIZE, ys * IMGSIZE) == -1)
				return (0);
	}
	return (1);
}

int	print_p(t_vars *vars, int xs, int ys)
{
	int	img_x;
	int	img_y;

	img_x = xs * IMGSIZE;
	img_y = ys * IMGSIZE;
	if (vars->map[ys][xs] == 'P')
	{
		if (mlx_image_to_window(vars->mlx, vars->player, img_x, img_y) == -1 \
		|| mlx_image_to_window(vars->mlx, vars->player_r, img_x, img_y) == -1 \
		|| mlx_image_to_window(vars->mlx, vars->player_l, img_x, img_y) == -1 \
		|| mlx_image_to_window(vars->mlx, vars->player_u, img_x, img_y) == -1 \
		|| mlx_image_to_window(vars->mlx, vars->player_d, img_x, img_y) == -1 \
		|| mlx_image_to_window(vars->mlx, vars->player_f, img_x, img_y) == -1)
			return (0);
	}
	return (1);
}

int	print_c_x_e(t_vars *vars, int xs, int ys)
{
	int	img_x;
	int	img_y;

	img_x = xs * IMGSIZE;
	img_y = ys * IMGSIZE;
	if (vars->map[ys][xs] == 'C')
	{
		if (mlx_image_to_window(vars->mlx, vars->coll, img_x, img_y) == -1)
			return (0);
	}
	else if (vars->map[ys][xs] == 'X')
	{
		if (mlx_image_to_window(vars->mlx, vars->enemy, img_x, img_y) == -1 \
		|| mlx_image_to_window(vars->mlx, vars->skull, img_x, img_y) == -1)
			return (0);
	}
	else if (vars->map[ys][xs] == 'E')
	{
		if ((mlx_image_to_window(vars->mlx, vars->open, img_x, img_y) == -1 \
		|| mlx_image_to_window(vars->mlx, vars->gameexit, img_x, img_y) == -1))
			return (0);
	}
	return (1);
}

int	print_img(t_vars *vars, int xs, int ys)
{
	int	img_x;
	int	img_y;

	img_x = xs * IMGSIZE;
	img_y = ys * IMGSIZE;
	if (vars->map[ys][xs] == '1')
	{
		if (mlx_image_to_window(vars->mlx, vars->wall, img_x, img_y) == -1)
			return (0);
	}
	else if (vars->map[ys][xs] == 'C' || vars->map[ys][xs] == 'X' \
		|| vars->map[ys][xs] == 'E')
	{
		if (!print_c_x_e(vars, xs, ys))
			return (0);
	}
	else if (vars->map[ys][xs] == 'P')
	{
		if (!print_p(vars, xs, ys))
			return (0);
	}
	return (1);
}

int	print_map(t_vars *vars)
{
	int	xs;
	int	ys;

	ys = -1;
	if (!print_ground(vars))
		return (0);
	while (++ys < vars->size_y)
	{
		xs = -1;
		while (++xs < vars->size_x)
			if (!print_img(vars, xs, ys))
				return (0);
	}
	return (1);
}
