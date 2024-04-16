/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pics.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:22:40 by sung-hle          #+#    #+#             */
/*   Updated: 2023/05/28 17:12:31 by sung-hle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

mlx_image_t	*source_to_mlx_image_t(mlx_t *mlx, char *adress)
{
	xpm_t		*tmp;
	mlx_image_t	*img;

	tmp = mlx_load_xpm42(adress);
	if (!tmp)
		return (NULL);
	img = mlx_texture_to_image(mlx, &(tmp->texture));
	if (!img)
		return (NULL);
	mlx_delete_xpm42(tmp);
	return (img);
}

int	pics_init_one(t_vars *vars)
{
	vars->player = source_to_mlx_image_t(vars->mlx, "./pictures/smile.xpm42");
	if (vars->player == NULL)
		return (1);
	vars->ground = source_to_mlx_image_t(vars->mlx, "./pictures/gr_bl.xpm42");
	if (vars->ground == NULL)
		return (1);
	vars->wall = source_to_mlx_image_t(vars->mlx, "./pictures/wall02.xpm42");
	if (vars->wall == NULL)
		return (1);
	return (0);
}

int	pics_init_two(t_vars *vars)
{
	vars->coll = source_to_mlx_image_t(vars->mlx, "./pictures/coll.xpm42");
	if (vars->coll == NULL)
		return (1);
	vars->gameexit = source_to_mlx_image_t(vars->mlx, "./pictures/exit.xpm42");
	if (vars->gameexit == NULL)
		return (1);
	vars->open = source_to_mlx_image_t(vars->mlx, "./pictures/open.xpm42");
	if (vars->open == NULL)
		return (1);
	return (0);
}

int	start_and_error(int argc, char **argv, t_vars *vars)
{
	int		i;
	char	*joined;
	char	**split;

	i = 0;
	if (argc != 2)
		return (ft_error_sl("Error\nNumber of args has to be 2\n"));
	if (!check_suffix(argv[1]))
		return (ft_error_sl("Error\nno valid suffix\n"));
	joined = read_file(argv[1], &i);
	if (joined == NULL)
		return (ft_error_sl("Error\nread with error\n"));
	split = ft_split(joined, '\n');
	if (split == NULL)
		return (ft_error_sl("Error\nsplit with error\n"));
	vars->map = split;
	ft_so_long_init(vars, i);
	free(joined);
	if (error_check(vars, i))
		return (2);
	return (0);
}
