/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_casting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 09:38:33 by fhassoun          #+#    #+#             */
/*   Updated: 2023/09/13 12:27:04 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	texturing_calculation(t_cub *cub)
{
	cub->data.tex_num = cub->config->maps[cub->data.map_x][cub->data.map_y]
		- 1; 
	if (cub->data.side == 0)
		cub->data.wall_x = cub->data.pos_y + cub->data.perp_wall_dist
			* cub->data.raydir_y;
	else
		cub->data.wall_x = cub->data.pos_x + cub->data.perp_wall_dist
			* cub->data.raydir_x;
	cub->data.wall_x -= floor((cub->data.wall_x));
	cub->data.tex_x = (int)(cub->data.wall_x * (double)TEXWIDTH);
	if (cub->data.side == 0 && cub->data.raydir_x > 0)
		cub->data.tex_x = TEXWIDTH - cub->data.tex_x - 1;
	if (cub->data.side == 1 && cub->data.raydir_y < 0)
		cub->data.tex_x = TEXWIDTH - cub->data.tex_x - 1;
	cub->data.step = 1.0 * TEXHEIGHT / cub->data.line_height;
	cub->data.tex_pos = (cub->data.draw_start - SCREENHEIGHT / 2
			+ cub->data.line_height / 2) * cub->data.step;
}

void	select_direction(t_cub *cub)
{
	cub->data.tex_y = (int)cub->data.tex_pos & (TEXHEIGHT - 1);
	cub->data.tex_pos += cub->data.step;
	if (cub->data.side == 0)
	{
		if (cub->data.raydir_x > 0)
			cub->data.tex_num = 1;
		else
			cub->data.tex_num = 0;
	}
	else if (cub->data.side == 1)
	{
		if (cub->data.raydir_y > 0)
			cub->data.tex_num = 3;
		else
			cub->data.tex_num = 2;
	}
}

void	wall_casting(t_cub *cub)
{
	int	x;
	int	y;

	x = 0;
	while (x < SCREENWIDTH)
	{
		y = 0;
		initial_calculations(cub, x);
		calculate_step_and_sidedist(cub);
		perform_dda(cub);
		calculate_camera_distance(cub);
		calc_height_and_pix(cub);
		texturing_calculation(cub);
		y = cub->data.draw_start;
		while (y < cub->data.draw_end)
		{
			select_direction(cub);
			cub->data.color = get_color_from_pixel(
					(uint8_t *)&cub->texture[cub->data.tex_num][TEXHEIGHT
					* cub->data.tex_y + cub->data.tex_x]);
			cub->buffer[y][x] = cub->data.color;
			y++;
		}
		x++;
	}
}
