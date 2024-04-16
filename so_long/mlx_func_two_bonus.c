/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_func_two_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:53:20 by sung-hle          #+#    #+#             */
/*   Updated: 2023/11/23 16:24:33 by sung-hle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	set_image_depth(mlx_image_t *image, int z)
{
	int	i;

	i = 0;
	while (i < (int)image->count)
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
	char	*itoa;

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
	if (pic == vars->blink->b && vars->win_lose_flag == 0)
		ft_printf("steps %d\n", ++vars->steps);
	if (vars->mlx_outputstring != NULL)
		mlx_delete_image(vars->mlx, vars->mlx_outputstring);
	itoa = ft_itoa(vars->steps);
	vars->mlx_outputstring = mlx_put_string(vars->mlx, itoa, 0, 0);
	free(itoa);
	return (0);
}

int	checker_collectible(t_vars *vars)
{
	int	xs;
	int	ys;

	xs = vars->blink->b->instances[0].x / IMGSIZE;
	ys = vars->blink->b->instances[0].y / IMGSIZE;
	if (vars->map[ys][xs] == 'C')
	{
		vars->coll->instances[which_instance(vars)].enabled = false;
		vars->map[ys][xs] = '0';
		vars->c_ctr--;
		if (vars->c_ctr == 0)
		{
			vars->gameexit->instances[0].enabled = false;
			vars->open->instances[0].enabled = true;
			vars->player->instances[0].x = vars->blink->b->instances[0].x;
			vars->player->instances[0].y = vars->blink->b->instances[0].y;
			vars->blink->b->instances[0].enabled = false;
			vars->player->instances[0].enabled = true;
			vars->blink->b = vars->player;
		}
		return (1);
	}
	return (0);
}

void	blinky_player(t_vars *vars)
{
	if (vars->hook_loop % 30 < 15)
	{
		vars->blink->a->instances[0].x = vars->blink->b->instances[0].x;
		vars->blink->a->instances[0].y = vars->blink->b->instances[0].y;
		vars->blink->a->instances[0].enabled = true;
		vars->blink->b->instances[0].enabled = false;
	}
	else
	{
		vars->blink->b->instances[0].enabled = true;
		vars->blink->a->instances[0].enabled = false;
	}
}

void	blinky_enemy(t_vars *vars)
{
	int	i;

	i = -1;
	while (++i < vars->x_ctr)
	{
		if (((vars->hook_loop) % vars->x_blink) < (vars->x_blink / 2))
		{
			vars->skull->instances[i].x = vars->enemy->instances[i].x;
			vars->skull->instances[i].y = vars->enemy->instances[i].y;
			vars->skull->instances[i].enabled = true;
			vars->enemy->instances[i].enabled = false;
		}
		else
		{
			vars->enemy->instances[i].enabled = true;
			vars->skull->instances[i].enabled = false;
		}
	}
}
