/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_bonus_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:58:22 by sung-hle          #+#    #+#             */
/*   Updated: 2023/05/26 17:01:18 by sung-hle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	terminate(t_vars *vars, int ret)
{
	if (ret)
	{
		ft_printf("Error\n");
		mlx_terminate(vars->mlx);
		return (1);
	}
	return (0);
}

int	level_up(t_vars *vars, char **argv, char **lev2, char **lev3)
{
	t_vars	level_two;
	t_vars	level_three;

	level_two.win_lose_flag = 0;
	if (terminate_level(vars, levels(2, argv, vars)))
		return (1);
	if (vars->win_lose_flag == 2)
		if (terminate_level(&level_two, levels(2, lev2, &level_two)))
			return (1);
	level_three.win_lose_flag = 0;
	if (level_two.win_lose_flag == 2)
		if (terminate_level(&level_three, levels(2, lev3, &level_three)))
			return (1);
	if (level_three.win_lose_flag == 2)
	{
		if (init_endscreen(2))
			return (1);
	}
	else if (vars->win_lose_flag == 1 || level_two.win_lose_flag == 1
		|| level_three.win_lose_flag == 1)
		if (init_endscreen(1))
			return (1);
	return (0);
}

void	my_key_func2(mlx_key_data_t keydata, void *bla)
{
	mlx_t	*mlx;

	mlx = bla;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(mlx);
}

void	ft_hook2(void *mlx)
{
	mlx_key_hook(mlx, &my_key_func2, mlx);
}

void	set_depth(t_vars *vars)
{
	set_image_depth(vars->ground, L_GROUND);
	set_image_depth(vars->wall, L_WALL);
	set_image_depth(vars->coll, L_COLLECTIBLE);
	set_image_depth(vars->player, L_PLAYER);
	set_image_depth(vars->player_f, L_PLAYER);
	set_image_depth(vars->player_r, L_PLAYER);
	vars->player_r->instances[0].enabled = false;
	set_image_depth(vars->player_l, L_PLAYER);
	vars->player_l->instances[0].enabled = false;
	set_image_depth(vars->player_u, L_PLAYER);
	vars->player_u->instances[0].enabled = false;
	set_image_depth(vars->player_d, L_PLAYER);
	vars->player_d->instances[0].enabled = false;
	set_image_depth(vars->gameexit, L_EXIT);
	set_image_depth(vars->open, L_EXIT);
	vars->open->instances[0].enabled = false;
	set_image_depth(vars->enemy, L_PLAYER);
}
