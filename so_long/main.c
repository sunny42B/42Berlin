/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:54:30 by sung-hle          #+#    #+#             */
/*   Updated: 2023/05/29 16:21:02 by sung-hle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_so_long_init(t_vars *vars, int i)
{
	vars->p_ctr = 0;
	vars->e_ctr = 0;
	vars->c_ctr = 0;
	vars->size_y = i;
	vars->size_x = ft_strlen(vars->map[0]);
	vars->steps = 0;
	vars->win_lose_flag = 0;
	vars->start.x = 0;
	vars->start.y = 0;
}

int	terminate_level(t_vars *vars, int ret)
{
	if (ret)
	{
		ft_printf("Error\npics- and print-error\n");
		mlx_terminate(vars->mlx);
		ft_free(vars->map);
		return (1);
	}
	return (0);
}

int	levels(int argc, char **argv, t_vars *vars)
{
	if (start_and_error(argc, argv, vars))
		return (1);
	vars->mlx = mlx_init(vars->size_x * IMGSIZE, vars->size_y * IMGSIZE, \
		argv[0], true);
	if (!(vars->mlx))
		return (1);
	mlx_set_window_pos(vars->mlx, 0, 0);
	if (terminate(vars, pics_init_one(vars)) || terminate(vars, \
		pics_init_two(vars)) || terminate(vars, !print_map(vars)))
		return (1);
	set_depth(vars);
	mlx_loop_hook(vars->mlx, ft_hook, vars);
	mlx_loop(vars->mlx);
	mlx_terminate(vars->mlx);
	ft_free(vars->map);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_vars	vars;

	if (levels(argc, argv, &vars))
		return (1);
	return (0);
}
