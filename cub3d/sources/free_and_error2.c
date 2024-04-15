/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_error2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:32:04 by fhassoun          #+#    #+#             */
/*   Updated: 2023/09/19 13:23:35 by sung-hle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_message(char *error_message)
{
	ft_printf("Error\n%s\n", error_message);
}

void	error(void)
{
	ft_printf(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int	error_check(t_cub *cub, char *joined)
{
	if (line_check(cub, joined))
		return (1);
	if (valid_chars(cub->config->map))
		return (1);
	if (wall_check(cub, cub->config->map))
		return (1);
	return (0);
}

int	start_and_error(int argc, char **argv, t_cub *cub)
{
	int		i;
	char	*joined;
	char	**split;

	i = 0;
	if (argc != 2)
		return (ft_error_sl("Error\nNumber of args has to be 2\n"));
	if (!check_suffix(argv[1]))
		return (free(cub), ft_error_sl("Error\nno valid suffix\n"));
	joined = read_file(argv[1], &i);
	if (joined == NULL)
		return (ft_error_sl("Error\nread with error\n"));
	split = ft_split(joined, '\n');
	if (split == NULL)
		return (free(joined), ft_error_sl("Error\nsplit with error\n"));
	if (parse_map(cub, split))
		return (ft_free(split), free(joined), 1);
	if (error_check(cub, joined))
		return (ft_free(split), free(joined), free_the_shit(cub), 1);
	ft_free(split);
	free(joined);
	return (0);
}

void	free_texture(t_cub *cub)
{
	if (cub->tex0)
		mlx_delete_xpm42(cub->tex0);
	if (cub->tex1)
		mlx_delete_xpm42(cub->tex1);
	if (cub->tex2)
		mlx_delete_xpm42(cub->tex2);
	if (cub->tex3)
		mlx_delete_xpm42(cub->tex3);
	free(cub->texture);
}
