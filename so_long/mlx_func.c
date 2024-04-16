/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:54:42 by sung-hle          #+#    #+#             */
/*   Updated: 2023/05/25 16:53:08 by sung-hle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	win_func(t_vars *vars)
{
	if (vars->open->instances[0].x == vars->player->instances[0].x && \
		vars->open->instances[0].y == vars->player->instances[0].y && \
		vars->open->instances[0].z == L_EXIT && vars->c_ctr == 0)
	{
		vars->win_lose_flag = 2;
		ft_putstr_fd("You won!\n", 1);
		mlx_close_window(vars->mlx);
	}
}

void	key_stuff(mlx_key_data_t keydata, t_vars *vars)
{
	if ((keydata.key == MLX_KEY_DOWN) && (keydata.action == 1))
	{
		if (!checker_wall(vars, vars->player, 0, 2))
			vars->player->instances[0].y += IMGSIZE;
	}
	if ((keydata.key == MLX_KEY_LEFT) && (keydata.action == 1))
	{
		if (!checker_wall(vars, vars->player, 0, 3))
			vars->player->instances[0].x -= IMGSIZE;
	}
	if ((keydata.key == MLX_KEY_RIGHT) && (keydata.action == 1))
	{
		if (!checker_wall(vars, vars->player, 0, 4))
			vars->player->instances[0].x += IMGSIZE;
	}
}

void	my_key_func(mlx_key_data_t keydata, void *bla)
{
	t_vars	*vars;

	vars = bla;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(vars->mlx);
	else
	{
		if ((keydata.key == MLX_KEY_UP) && (keydata.action == 1))
		{
			if (!checker_wall(vars, vars->player, 0, 1))
				vars->player->instances[0].y -= IMGSIZE;
		}
		if (((keydata.key == MLX_KEY_DOWN) && (keydata.action == 1)) \
			|| ((keydata.key == MLX_KEY_LEFT) && (keydata.action == 1)) \
			|| ((keydata.key == MLX_KEY_RIGHT) && (keydata.action == 1)))
			key_stuff(keydata, vars);
		checker_collectible(vars);
		win_func(vars);
	}
}

void	ft_hook(void *vars)
{
	mlx_key_hook(((t_vars *)vars)->mlx, &my_key_func, vars);
}
