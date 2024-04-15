/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 10:43:11 by fhassoun          #+#    #+#             */
/*   Updated: 2023/09/19 13:24:33 by sung-hle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_textures(t_cub *cub)
{
	cub->texture = (int **)ft_calloc(sizeof(int *), 4);
	if (!cub->texture)
		return (error_message("Problem with malloc1"), 1);
	cub->tex0 = mlx_load_xpm42(cub->config->no);
	if (!cub->tex0)
		return (error_message("Problem with loading xpm1"), 1);
	cub->texture[0] = (int *)cub->tex0->texture.pixels;
	cub->tex1 = mlx_load_xpm42(cub->config->so);
	if (!cub->tex1)
		return (error_message("Problem with loading xpm2"), 1);
	cub->texture[1] = (int *)cub->tex1->texture.pixels;
	cub->tex2 = mlx_load_xpm42(cub->config->we);
	if (!cub->tex2)
		return (error_message("Problem with loading xpm3"), 1);
	cub->texture[2] = (int *)cub->tex2->texture.pixels;
	cub->tex3 = mlx_load_xpm42(cub->config->ea);
	if (!cub->tex3)
		return (error_message("Problem with loading xpm4"), 1);
	cub->texture[3] = (int *)cub->tex3->texture.pixels;
	return (0);
}
