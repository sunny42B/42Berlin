/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 10:49:31 by sung-hle          #+#    #+#             */
/*   Updated: 2023/09/13 09:46:10 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_after_read_list(t_cub *cub, t_list *head)
{
	t_list	*tmp;

	tmp = head;
	while (tmp != NULL)
	{
		ft_putendl_fd((char *)tmp->content, 1);
		tmp = tmp->next;
	}
	ft_putendl_fd(cub->config->no, 1);
	ft_putendl_fd(cub->config->so, 1);
	ft_putendl_fd(cub->config->ea, 1);
	ft_putendl_fd(cub->config->we, 1);
	ft_putnbr_fd(cub->config->f, 1);
	ft_putendl_fd("", 1);
	ft_putnbr_fd(cub->config->c, 1);
	ft_putendl_fd("", 1);
}

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
		printf("%s\n", map[i++]);
}

void	print_config(t_cub *cub)
{
	printf("%s\n", cub->config->no);
	printf("%s\n", cub->config->so);
	printf("%s\n", cub->config->ea);
	printf("%s\n", cub->config->we);
	printf("F: %x\n", cub->config->f);
	printf("C: %x\n", cub->config->c);
	print_map(cub->config->map);
}

void	print_int_arr_plus(t_cub *cub)
{
	int	i;
	int	j;

	printf("%s\n", cub->config->no);
	printf("%s\n", cub->config->so);
	printf("%s\n", cub->config->ea);
	printf("%s\n", cub->config->we);
	printf("F: %x\n", cub->config->f);
	printf("C: %x\n", cub->config->c);
	i = 0;
	while (i < cub->config->map_h)
	{
		j = 0;
		while (j < cub->config->map_w)
		{
			if (j < cub->config->map_w - 1)
				printf("%i, ", cub->config->maps[i][j]);
			else
				printf("%i\n", cub->config->maps[i][j]);
			j++;
		}
		i++;
	}
}
