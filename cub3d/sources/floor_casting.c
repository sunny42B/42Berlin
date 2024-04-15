/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_casting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:22:30 by fhassoun          #+#    #+#             */
/*   Updated: 2023/09/13 12:26:48 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	floor_casting_calculations(t_cub *cub, int y)
// line 30 - 33: rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
// line 34:	Current y position compared to the center of the screen (horizon)
// line 35:	Vertical position of the camera.
// line 36:	Horiz. distance from the camera to the floor for the current row.
// 			0.5 is z position exactly in the middle between floor and ceiling
// line 37 - 40:	calculate the real world step vector we have to add 
//				for each x(parallel to camera plane)
// 				adding step by step avoids multiplications with a
//				weight in the inner loop
// line 41 - 44:	real world coordinates of the leftmost column. This will
//				be updated as we step to the right.
{
	cub->data.raydir_x0 = cub->data.dir_x - cub->data.plane_x;
	cub->data.raydir_y0 = cub->data.dir_y - cub->data.plane_y;
	cub->data.raydir_x1 = cub->data.dir_x + cub->data.plane_x;
	cub->data.raydir_y1 = cub->data.dir_y + cub->data.plane_y;
	cub->data.p = y - SCREENHEIGHT / 2;
	cub->data.pos_z = 0.5 * SCREENHEIGHT;
	cub->data.row_distance = cub->data.pos_z / cub->data.p;
	cub->data.floorstep_x = cub->data.row_distance * (cub->data.raydir_x1
			- cub->data.raydir_x0) / SCREENWIDTH;
	cub->data.floorstep_y = cub->data.row_distance * (cub->data.raydir_y1
			- cub->data.raydir_y0) / SCREENWIDTH;
	cub->data.floor_x = cub->data.pos_x + cub->data.row_distance
		* cub->data.raydir_x0;
	cub->data.floor_y = cub->data.pos_y + cub->data.row_distance
		* cub->data.raydir_y0;
}

void	floor_casting(t_cub *cub)
{
	int	y;
	int	x;

	y = 0;
	while (y < SCREENHEIGHT)
	{
		floor_casting_calculations(cub, y);
		x = 0;
		while (x < SCREENWIDTH)
		{
			cub->data.floor_x += cub->data.floorstep_x;
			cub->data.floor_y += cub->data.floorstep_y;
			cub->data.color = cub->config->f;
			cub->buffer[y][x] = cub->data.color;
			cub->data.color = cub->config->c;
			cub->buffer[SCREENHEIGHT - y - 1][x] = cub->data.color;
			x++;
		}
		y++;
	}
}
