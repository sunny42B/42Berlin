/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_casting_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:12:46 by fhassoun          #+#    #+#             */
/*   Updated: 2023/09/13 12:27:10 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initial_calculations(t_cub *cub, int x)
//line 21:		calculate ray position and direction
//line 22-25:	x-coordinate in camera space
//line 26-27:	which box of the map we're in
//line 28-34:	length of ray from one x or y-side to next x or y-side
{
	cub->data.camera_x = 2 * x / (double)SCREENWIDTH - 1;
	cub->data.raydir_x = cub->data.dir_x + cub->data.plane_x
		* cub->data.camera_x;
	cub->data.raydir_y = cub->data.dir_y + cub->data.plane_y
		* cub->data.camera_x;
	cub->data.map_x = (int)cub->data.pos_x;
	cub->data.map_y = (int)cub->data.pos_y;
	cub->data.delta_dist_x = sqrt(1 + (cub->data.raydir_y
				* cub->data.raydir_y) / (cub->data.raydir_x
				* cub->data.raydir_x));
	cub->data.delta_dist_y = sqrt(1 + (cub->data.raydir_x
				* cub->data.raydir_x) / (cub->data.raydir_y
				* cub->data.raydir_y));
	cub->data.hit = 0;
}

void	calculate_step_and_sidedist(t_cub *cub)
// calculate step and initial sideDist
{
	if (cub->data.raydir_x < 0)
	{
		cub->data.step_x = -1;
		cub->data.side_dist_x = (cub->data.pos_x - cub->data.map_x)
			* cub->data.delta_dist_x;
	}
	else
	{
		cub->data.step_x = 1;
		cub->data.side_dist_x = (cub->data.map_x + 1.0 - cub->data.pos_x)
			* cub->data.delta_dist_x;
	}
	if (cub->data.raydir_y < 0)
	{
		cub->data.step_y = -1;
		cub->data.side_dist_y = (cub->data.pos_y - cub->data.map_y)
			* cub->data.delta_dist_y;
	}
	else
	{
		cub->data.step_y = 1;
		cub->data.side_dist_y = (cub->data.map_y + 1.0 - cub->data.pos_y)
			* cub->data.delta_dist_y;
	}
}

void	perform_dda(t_cub *cub)
{
	while (cub->data.hit == 0)
	{
		if (cub->data.side_dist_x < cub->data.side_dist_y)
		{
			cub->data.side_dist_x += cub->data.delta_dist_x;
			cub->data.map_x += cub->data.step_x;
			cub->data.side = 0;
		}
		else
		{
			cub->data.side_dist_y += cub->data.delta_dist_y;
			cub->data.map_y += cub->data.step_y;
			cub->data.side = 1;
		}
		if (cub->config->maps[cub->data.map_x][cub->data.map_y] > 0)
			cub->data.hit = 1;
	}
}

void	calculate_camera_distance(t_cub *cub)
// Calculate distance projected on camera direction
{
	if (cub->data.side == 0)
		cub->data.perp_wall_dist = (cub->data.map_x - cub->data.pos_x + (1
					- cub->data.step_x) / 2) / cub->data.raydir_x;
	else
		cub->data.perp_wall_dist = (cub->data.map_y - cub->data.pos_y + (1
					- cub->data.step_y) / 2) / cub->data.raydir_y;
}

void	calc_height_and_pix(t_cub *cub)
//line 102:		Calculate height of line to draw on screen
//line 103-108:	Calculate lowest and highest pixel to fill in current stripe
{
	cub->data.line_height = (int)(SCREENHEIGHT / cub->data.perp_wall_dist);
	cub->data.draw_start = -cub->data.line_height / 2 + SCREENHEIGHT / 2;
	if (cub->data.draw_start < 0)
		cub->data.draw_start = 0;
	cub->data.draw_end = cub->data.line_height / 2 + SCREENHEIGHT / 2;
	if (cub->data.draw_end >= SCREENHEIGHT)
		cub->data.draw_end = SCREENHEIGHT - 1;
}
