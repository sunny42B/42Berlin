/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_func_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:54:27 by sung-hle          #+#    #+#             */
/*   Updated: 2023/05/24 16:54:43 by sung-hle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	win_func(t_vars *vars)
{
	if (vars->open->instances[0].x == vars->blink->b->instances[0].x && \
		vars->open->instances[0].y == vars->blink->b->instances[0].y && \
		vars->open->instances[0].z == L_EXIT && vars->c_ctr == 0)
	{
		vars->win_lose_flag = 2;
		ft_putstr_fd("You won!\n", 1);
		mlx_close_window(vars->mlx);
	}
}

void	change_textures(t_vars *vars, mlx_image_t *a, mlx_image_t *b)
{
	a->instances[0].x = b->instances[0].x;
	a->instances[0].y = b->instances[0].y;
	vars->blink->a->instances[0].enabled = false;
	a->instances[0].enabled = true;
	vars->blink->a = a;
}

void	key_stuff(mlx_key_data_t keydata, t_vars *vars)
{
	if ((keydata.key == MLX_KEY_DOWN) && (keydata.action == 1))
	{
		if (!checker_wall(vars, vars->blink->b, 0, 2))
		{
			vars->blink->b->instances[0].y += IMGSIZE;
			change_textures(vars, vars->player_d, vars->blink->b);
		}
	}
	if ((keydata.key == MLX_KEY_LEFT) && (keydata.action == 1))
	{
		if (!checker_wall(vars, vars->blink->b, 0, 3))
		{
			vars->blink->b->instances[0].x -= IMGSIZE;
			change_textures(vars, vars->player_l, vars->blink->b);
		}
	}
	if ((keydata.key == MLX_KEY_RIGHT) && (keydata.action == 1))
	{
		if (!checker_wall(vars, vars->blink->b, 0, 4))
		{
			vars->blink->b->instances[0].x += IMGSIZE;
			change_textures(vars, vars->player_r, vars->blink->b);
		}
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
			if (!checker_wall(vars, vars->blink->b, 0, 1))
			{
				vars->blink->b->instances[0].y -= IMGSIZE;
				change_textures(vars, vars->player_u, vars->blink->b);
			}
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
	t_vars	*bla;

	bla = vars;
	bla->hook_loop++;
	if (bla->c_ctr < 3)
	{
		bla->x_blink = 24;
		bla->x_move = 24;
	}
	blinky_player(bla);
	blinky_enemy(bla);
	if (enemies((t_vars *)vars))
		return ;
	mlx_key_hook(((t_vars *)vars)->mlx, &my_key_func, vars);
}
