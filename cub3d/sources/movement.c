/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 09:03:58 by fhassoun          #+#    #+#             */
/*   Updated: 2023/09/13 12:19:26 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	strafe_left(t_cub *cub)
// strafe left if no wall in front of you
{
	if (cub->config->maps[(int)(cub->data.pos_x - cub->data.plane_x
			* cub->data.move_speed)][(int)(cub->data.pos_y)] == false)
		cub->data.pos_x -= cub->data.plane_x * cub->data.move_speed;
	if (cub->config->maps[(int)(cub->data.pos_x)][(int)(cub->data.pos_y
			- cub->data.plane_y * cub->data.move_speed)] == false)
		cub->data.pos_y -= cub->data.plane_y * cub->data.move_speed;
}

void	strafe_right(t_cub *cub)
// strafe right if no wall in front of you
{
	if (cub->config->maps[(int)(cub->data.pos_x + cub->data.plane_x
			* cub->data.move_speed)][(int)(cub->data.pos_y)] == false)
		cub->data.pos_x += cub->data.plane_x * cub->data.move_speed;
	if (cub->config->maps[(int)(cub->data.pos_x)][(int)(cub->data.pos_y
			+ cub->data.plane_y * cub->data.move_speed)] == false)
		cub->data.pos_y += cub->data.plane_y * cub->data.move_speed;
}

void	movement(t_cub *cub)
{
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub->mlx);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_UP) || mlx_is_key_down(cub->mlx,
			MLX_KEY_W))
		move_forward(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_DOWN) || mlx_is_key_down(cub->mlx,
			MLX_KEY_S))
		move_backward(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT) || mlx_is_key_down(cub->mlx,
			MLX_KEY_A))
		move_left(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT) || mlx_is_key_down(cub->mlx,
			MLX_KEY_D))
		move_right(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_Q))
		strafe_left(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_E))
		strafe_right(cub);
}
