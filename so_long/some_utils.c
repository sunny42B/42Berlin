/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 19:25:43 by sung-hle          #+#    #+#             */
/*   Updated: 2023/05/29 16:16:58 by sung-hle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

int	setting_ctrs(t_vars *vars, int j, int k, char c)
{
	if (c != 'P' && c != 'C' && c != 'E' && c != '0' && c != '1')
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
	return (1);
}
