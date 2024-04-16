/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:47:31 by sung-hle          #+#    #+#             */
/*   Updated: 2023/05/29 18:24:23 by sung-hle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_so_long_init(t_vars *vars, int i)
{
	vars->p_ctr = 0;
	vars->e_ctr = 0;
	vars->c_ctr = 0;
	vars->x_ctr = 0;
	vars->x_blink = 40;
	vars->x_move = 50;
	vars->hook_loop = 0;
	vars->size_y = i;
	vars->size_x = ft_strlen(vars->map[0]);
	vars->steps = 0;
	vars->win_lose_flag = 0;
	vars->start.x = 0;
	vars->start.y = 0;
	vars->mlx_outputstring = NULL;
}

int	terminate_level(t_vars *vars, int ret)
{
	if (ret)
	{
		ft_printf("Error\npics- and print-error\n");
		mlx_terminate(vars->mlx);
		free(vars->blink);
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
		pics_init_two(vars)) || terminate(vars, pics_init_three(vars)) \
		|| terminate(vars, !print_map(vars)))
		return (1);
	vars->blink = malloc(sizeof (t_blink));
	if (!vars->blink)
		return (1);
	vars->blink->a = vars->player;
	vars->blink->b = vars->player_f;
	set_depth(vars);
	mlx_loop_hook(vars->mlx, ft_hook, vars);
	mlx_loop(vars->mlx);
	mlx_terminate(vars->mlx);
	free(vars->blink);
	ft_free(vars->map);
	return (0);
}

int	init_endscreen(int flag)
{
	mlx_t		*mlx;
	mlx_image_t	*endscreen;

	endscreen = NULL;
	mlx = mlx_init(900, 150, "SO_LONG", true);
	if (!mlx)
		return (1);
	mlx_set_window_pos(mlx, 100, 100);
	if (flag == 1)
		endscreen = source_to_mlx_image_t(mlx, "./pictures/youdied.xpm42");
	else
		endscreen = source_to_mlx_image_t(mlx, "./pictures/winner.xpm42");
	if (endscreen == NULL)
	{
		mlx_terminate(mlx);
		return (1);
	}
	mlx_resize_image(endscreen, 900, 150);
	mlx_image_to_window(mlx, endscreen, 0, 0);
	mlx_loop_hook(mlx, ft_hook2, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_vars	vars;
	char	*lev1[2];
	char	*lev2[2];
	char	*lev3[2];

	if (argc != 1)
		return (ft_printf("just hit './so_long_bonus'\n"));
	(void) argv;
	lev1[0] = "2";
	lev1[1] = "maps/lvl1_bonus.ber";
	lev2[0] = "2";
	lev2[1] = "maps/lvl2_bonus.ber";
	lev3[0] = "2";
	lev3[1] = "maps/below_easy.ber";
	if (level_up(&vars, lev1, lev2, lev3))
		return (1);
	return (0);
}
