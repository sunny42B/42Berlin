/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 18:23:09 by sung-hle          #+#    #+#             */
/*   Updated: 2023/09/13 11:36:15 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_error_sl(char *s)
{
	ft_putstr_fd(s, 1);
	return (1);
}

void	free_the_shit(t_cub *cub)
{
	if (cub->config->map != NULL)
		ft_free(cub->config->map);
	if (cub->config->no != NULL)
		free(cub->config->no);
	if (cub->config->so != NULL)
		free(cub->config->so);
	if (cub->config->ea != NULL)
		free(cub->config->ea);
	if (cub->config->we != NULL)
		free(cub->config->we);
	if (cub->config->maps != NULL)
		free_int_two_d(cub);
	if (cub->config != NULL)
		free(cub->config);
	if (cub->texture != NULL)
		free_texture(cub);
	if (cub != NULL)
		free(cub);
}

void	free_int_two_d(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < cub->config->map_h)
		free(cub->config->maps[i++]);
	free(cub->config->maps);
}

int	free_paths(char **path)
{
	if (*path != NULL)
	{
		free(*path);
		*path = NULL;
		return (1);
	}
	return (0);
}

int	free_config(t_cub *cub, t_list *head)
{
	int	flag;

	flag = 0;
	flag = free_paths(&cub->config->no);
	flag = free_paths(&cub->config->so);
	flag = free_paths(&cub->config->we);
	flag = free_paths(&cub->config->ea);
	if (head != NULL)
	{
		flag = 1;
		ft_free_list(&head);
		head = NULL;
	}
	if (flag)
		return (1);
	return (0);
}
