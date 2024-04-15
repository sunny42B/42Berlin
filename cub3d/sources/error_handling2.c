/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:50:07 by sung-hle          #+#    #+#             */
/*   Updated: 2023/09/19 11:45:15 by sung-hle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_config_init(t_cub *cub)
{
	cub->config = (t_config *) malloc(sizeof(t_config));
	if (!cub->config)
		return (1);
	cub->config->no = NULL;
	cub->config->so = NULL;
	cub->config->we = NULL;
	cub->config->ea = NULL;
	cub->config->f = -2;
	cub->config->c = -2;
	cub->config->spawn_dir = -1;
	cub->config->spawn_x = -1;
	cub->config->spawn_y = -1;
	cub->config->map_w = -1;
	cub->config->map_h = -1;
	cub->config->map = NULL;
	cub->config->maps = NULL;
	return (0);
}

char	**dup_map(t_cub *cub, char **original)
{
	int		i;
	char	**new;
	int		len;

	i = 0;
	new = malloc((cub->config->map_h + 1) * sizeof(char *));
	if (new == NULL)
		return (NULL);
	while (i < cub->config->map_h)
	{
		len = ft_strlen(original[i]) + 1;
		new[i] = malloc(len * sizeof(char));
		if (new[i] == NULL)
		{
			ft_free(new);
			return (NULL);
		}
		ft_strlcpy(new[i], original[i], len);
		i++;
	}
	new[i] = NULL;
	return (new);
}

void	free_int_map(int **arr, int i)
{
	while (i--)
		free(arr[i]);
	free(arr);
}

void	fill_int_arr(t_cub *cub, char **map, int i)
{
	int	j;

	j = 0;
	while (j < (int)ft_strlen(map[i]))
	{
		if (is_map(map[i][j]))
			cub->config->maps[i][j] = map[i][j] - '0';
		else if (map[i][j] == ' ')
			cub->config->maps[i][j] = 0;
		else if (is_player(map[i][j]))
		{
			cub->config->spawn_x = i;
			cub->config->spawn_y = j;
			cub->config->spawn_dir = map[i][j];
			cub->config->maps[i][j] = 0;
		}
		j++;
	}
}

int	convert_map(t_cub *cub, char **map)
{
	int	i;

	i = 0;
	cub->config->maps = (int **) malloc(sizeof(int *) * cub->config->map_h);
	ft_memset(cub->config->maps, '\0', sizeof(int *));
	if (!cub->config->maps)
		return (printf("error, malloc 2d int arr\n"), 1);
	while (map[i] != NULL)
	{
		cub->config->maps[i] = malloc(sizeof(int) * cub->config->map_w);
		ft_memset(cub->config->maps[i], 0, sizeof(int) * cub->config->map_w);
		if (!cub->config->maps[i])
			return (free_int_map(cub->config->maps, i), \
				printf("error, malloc int*\n"), 1);
		fill_int_arr(cub, map, i);
		i++;
	}
	return (0);
}
