/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 08:59:03 by fhassoun          #+#    #+#             */
/*   Updated: 2023/09/19 13:26:36 by sung-hle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	get_color_from_pixel(uint8_t *pixel)
{
	return (pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]);
}

void	spawn_dir(t_cub *cub)
/*
** Set Player direction and camera plane according to spawn direction
*/
{
	if (cub->config->spawn_dir == 'N')
		return ;
	else if (cub->config->spawn_dir == 'E')
	{
		cub->data.dir_x = 0;
		cub->data.dir_y = 1;
		cub->data.plane_x = 0.66;
		cub->data.plane_y = 0;
	}
	else if (cub->config->spawn_dir == 'S')
	{
		cub->data.dir_x = 1;
		cub->data.dir_y = 0;
		cub->data.plane_x = 0;
		cub->data.plane_y = -0.66;
	}
	else if (cub->config->spawn_dir == 'W')
	{
		cub->data.dir_x = 0;
		cub->data.dir_y = -1;
		cub->data.plane_x = -0.66;
		cub->data.plane_y = 0;
	}
	return ;
}
// -----------------------------------------------------------------------------

int	init_game(t_cub *cub)
{
	cub->data.pos_x = cub->config->spawn_x + 0.5;
	cub->data.pos_y = cub->config->spawn_y + 0.5;
	cub->data.dir_x = -1;
	cub->data.dir_y = 0;
	cub->data.plane_x = 0;
	cub->data.plane_y = 0.66;
	spawn_dir(cub);
	cub->data.time = 0;
	cub->data.oldtime = 0;
	cub->data.move_speed = cub->data.frame_time;
	cub->data.rot_speed = cub->data.frame_time;
	cub->config->map_width = SCREENWIDTH;
	cub->config->map_height = SCREENHEIGHT;
	if (create_textures(cub) == 1)
		return (1);
	cub->mlx = mlx_init(cub->config->map_width, cub->config->map_height,
			"Cub3D", true);
	if (!(cub->mlx))
		error();
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub	*cub;

	if (argc != 2)
	{
		ft_printf("%s\n", "Usage: ./cub3d path/to/mapname.cub");
		return (EXIT_FAILURE);
	}
	cub = (t_cub *)ft_calloc(1, sizeof(t_cub));
	if (start_and_error(argc, argv, cub))
		return (1);
	if (convert_map(cub, cub->config->map))
		return (printf("error, convert_map malloc\n"), free_the_shit(cub), 1);
	if (init_game(cub) == 1)
		return (free_the_shit(cub), EXIT_FAILURE);
	mlx_loop_hook(cub->mlx, routine, cub);
	mlx_loop(cub->mlx);
	mlx_terminate(cub->mlx);
	free_the_shit(cub);
	return (EXIT_SUCCESS);
}
