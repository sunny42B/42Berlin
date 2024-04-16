/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:05:57 by sung-hle          #+#    #+#             */
/*   Updated: 2023/05/25 16:54:02 by sung-hle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	set_depth(t_vars *vars)
{
	set_image_depth(vars->ground, L_GROUND);
	set_image_depth(vars->wall, L_WALL);
	set_image_depth(vars->coll, L_COLLECTIBLE);
	set_image_depth(vars->player, L_PLAYER);
	set_image_depth(vars->gameexit, L_EXIT);
	set_image_depth(vars->open, L_EXIT);
	vars->open->instances[0].enabled = false;
}
