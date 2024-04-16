/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:56:23 by sung-hle          #+#    #+#             */
/*   Updated: 2023/05/24 16:56:51 by sung-hle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	check_lines(char *joined)
{
	int	i;

	i = -1;
	while (joined[++i])
		if (joined[i] == '\n' && joined[i + 1] == '\n')
			return (1);
	return (0);
}

int	cnt_maplines(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
		i++;
	return (i);
}

int	lose_func(t_vars *vars, int i)
{
	if (vars->enemy->instances[i].x == vars->blink->b->instances[0].x && \
		vars->enemy->instances[i].y == vars->blink->b->instances[0].y)
	{
		vars->win_lose_flag = 1;
		ft_putstr_fd("You lost!\n", 1);
		mlx_close_window(vars->mlx);
		return (1);
	}
	else
		return (0);
}

int	enemies(t_vars *vars)
{
	int	i;
	int	random;

	i = -1;
	random = 0;
	srand(time(NULL));
	while (++i < vars->x_ctr)
	{
		if (vars->hook_loop % vars->x_move == 0)
		{
			random = rand();
			if (!checker_wall(vars, vars->enemy, i, 1) && random % 4 == 0)
				vars->enemy->instances[i].y -= IMGSIZE;
			else if (!checker_wall(vars, vars->enemy, i, 2) && random % 4 == 1)
				vars->enemy->instances[i].y += IMGSIZE;
			else if (!checker_wall(vars, vars->enemy, i, 3) && random % 4 == 2)
				vars->enemy->instances[i].x -= IMGSIZE;
			else if (!checker_wall(vars, vars->enemy, i, 4) && random % 4 == 3)
				vars->enemy->instances[i].x += IMGSIZE;
		}
		if (lose_func(vars, i))
			return (1);
	}
	return (0);
}

int	setting_ctrs(t_vars *vars, int j, int k, char c)
{
	if (c != 'P' && c != 'C' && c != 'E' && c != 'X' && c != '0' && c != '1')
		return (0);
	else if (c == 'P')
	{
		vars->p_ctr++;
		vars->start.x = j;
		vars->start.y = k;
	}
	else if (c == 'C')
		vars->c_ctr++;
	else if (c == 'E')
	{
		vars->e_ctr++;
		vars->exit.x = j;
		vars->exit.y = k;
	}
	else if (c == 'X')
		vars->x_ctr++;
	return (1);
}
