/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:39:32 by fhassoun          #+#    #+#             */
/*   Updated: 2023/09/13 12:27:00 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_buffer(t_cub *cub)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREENHEIGHT)
	{
		x = 0;
		while (x < SCREENWIDTH)
		{
			cub->buffer[y][x] = 0;
			x++;
		}
		y++;
	}
}

void	switch_window(t_cub *cub, int frame)
{
	if (frame % 2 == 0)
	{
		mlx_delete_image(cub->mlx, cub->pic[1]);
		mlx_image_to_window(cub->mlx, cub->pic[0], 0, 0);
	}
	else
	{
		mlx_delete_image(cub->mlx, cub->pic[0]);
		mlx_image_to_window(cub->mlx, cub->pic[1], 0, 0);
	}
}

void	render(t_cub *cub, int frame)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREENHEIGHT)
	{
		x = 0;
		while (x < SCREENWIDTH)
		{
			if (frame % 2 == 0)
				mlx_put_pixel(cub->pic[0], x, y, cub->buffer[y][x]);
			else
				mlx_put_pixel(cub->pic[1], x, y, cub->buffer[y][x]);
			x++;
		}
		y++;
	}
}

void	routine(void *test)
{
	static int	frame = 0;
	t_cub		*cub;

	cub = (t_cub *)test;
	if (frame % 2 == 0)
		cub->pic[0] = mlx_new_image(cub->mlx, SCREENWIDTH, SCREENHEIGHT);
	else
		cub->pic[1] = mlx_new_image(cub->mlx, SCREENWIDTH, SCREENHEIGHT);
	floor_casting(cub);
	wall_casting(cub);
	render(cub, frame);
	switch_window(cub, frame);
	cub->data.oldtime = cub->data.time;
	cub->data.time = mlx_get_time();
	cub->data.frame_time = (cub->data.time - cub->data.oldtime);
	cub->data.move_speed = cub->data.frame_time * 5.0;
	cub->data.rot_speed = cub->data.frame_time * 3.0;
	movement(cub);
	clear_buffer(cub);
	frame++;
}
