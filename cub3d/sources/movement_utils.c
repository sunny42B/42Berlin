/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 09:21:16 by fhassoun          #+#    #+#             */
/*   Updated: 2023/09/13 12:19:26 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_cub *cub)
// move forward if no wall in front of you
{
	if (cub->config->maps[(int)(cub->data.pos_x + cub->data.dir_x
			* cub->data.move_speed)][(int)(cub->data.pos_y)] == false)
		cub->data.pos_x += cub->data.dir_x * cub->data.move_speed;
	if (cub->config->maps[(int)(cub->data.pos_x)][(int)(cub->data.pos_y
			+ cub->data.dir_y * cub->data.move_speed)] == false)
		cub->data.pos_y += cub->data.dir_y * cub->data.move_speed;
}

void	move_backward(t_cub *cub)
// move backwards if no wall behind you
{
	if (cub->config->maps[(int)(cub->data.pos_x - cub->data.dir_x
			* cub->data.move_speed)][(int)(cub->data.pos_y)] == false)
		cub->data.pos_x -= cub->data.dir_x * cub->data.move_speed;
	if (cub->config->maps[(int)(cub->data.pos_x)][(int)(cub->data.pos_y
			- cub->data.dir_y * cub->data.move_speed)] == false)
		cub->data.pos_y -= cub->data.dir_y * cub->data.move_speed;
}

void	move_left(t_cub *cub)
// both camera direction and camera plane must be rotated
{
	cub->data.olddir_x = cub->data.dir_x;
	cub->data.dir_x = cub->data.dir_x * cos(cub->data.rot_speed) - 
		cub->data.dir_y * sin(cub->data.rot_speed);
	cub->data.dir_y = cub->data.olddir_x * sin(cub->data.rot_speed)
		+ cub->data.dir_y * cos(cub->data.rot_speed);
	cub->data.oldplane_x = cub->data.plane_x;
	cub->data.plane_x = cub->data.plane_x * cos(cub->data.rot_speed)
		- cub->data.plane_y * sin(cub->data.rot_speed);
	cub->data.plane_y = cub->data.oldplane_x * sin(cub->data.rot_speed)
		+ cub->data.plane_y * cos(cub->data.rot_speed);
}

void	move_right(t_cub *cub)
// both camera direction and camera plane must be rotated
{
	cub->data.olddir_x = cub->data.dir_x;
	cub->data.dir_x = cub->data.dir_x * cos(-cub->data.rot_speed) - 
		cub->data.dir_y * sin(-cub->data.rot_speed);
	cub->data.dir_y = cub->data.olddir_x * sin(-cub->data.rot_speed)
		+ cub->data.dir_y * cos(-cub->data.rot_speed);
	cub->data.oldplane_x = cub->data.plane_x;
	cub->data.plane_x = cub->data.plane_x * cos(-cub->data.rot_speed)
		- cub->data.plane_y * sin(-cub->data.rot_speed);
	cub->data.plane_y = cub->data.oldplane_x * sin(-cub->data.rot_speed)
		+ cub->data.plane_y * cos(-cub->data.rot_speed);
}
