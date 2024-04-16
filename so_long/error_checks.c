/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:25:52 by sung-hle          #+#    #+#             */
/*   Updated: 2023/05/26 16:30:38 by sung-hle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	valid_chars(t_vars *vars, int i)
{
	int		j;
	size_t	k;
	char	**tmp;

	j = -1;
	tmp = vars->map;
	while (++j < i)
	{
		k = -1;
		while (++k < ft_strlen(tmp[j]))
			if (!setting_ctrs(vars, j, k, tmp[j][k]))
				return (0);
	}
	if (vars->p_ctr != 1 || vars->e_ctr != 1 || vars->c_ctr < 1)
		return (0);
	else
		return (1);
}

int	invalid_path(t_vars *vars, int i)
{
	char	**tmp;
	t_vars	dup;

	tmp = dup_string_arr(vars->map, i);
	dup.p_ctr = vars->p_ctr;
	dup.c_ctr = vars->c_ctr;
	dup.e_ctr = vars->e_ctr;
	dup.size_x = vars->size_x;
	dup.size_y = vars->size_y;
	flood_fill(tmp, &dup, vars->start);
	ft_free(tmp);
	if (dup.c_ctr > 0 || dup.e_ctr > 0)
		return (1);
	return (0);
}

int	error_check(t_vars *vars, int i)
{
	if (!same_length(vars, i))
		return (return_free_split(vars->map, "Error\nLine length wrong\n"));
	if (!line_check(vars, i))
		return (return_free_split(vars->map, "Error\nlines not valid\n"));
	if (!valid_chars(vars, i))
		return (return_free_split(vars->map, "Error\nnot valid chars\n"));
	if (invalid_path(vars, i))
		return (return_free_split(vars->map, "Error\nno valid path\n"));
	return (0);
}

void	f_fill(char **tab, t_vars *vars, char target, t_point begin)
{
	int	row;
	int	col;

	row = begin.x;
	col = begin.y;
	if ((row < 0 || col < 0 || row >= vars->size_y || col >= vars->size_x) || \
		(tab[row][col] == '1') || (vars->c_ctr == 0 && vars->e_ctr == 0))
		return ;
	else if (tab[row][col] == 'P')
		vars->p_ctr--;
	else if (tab[row][col] == 'E')
		vars->e_ctr--;
	else if (tab[row][col] == 'C')
		vars->c_ctr--;
	tab[row][col] = '1';
	begin.x -= 1;
	f_fill(tab, vars, target, begin);
	begin.x += 2;
	f_fill(tab, vars, target, begin);
	begin.y -= 1;
	begin.x -= 1;
	f_fill(tab, vars, target, begin);
	begin.y += 2;
	f_fill(tab, vars, target, begin);
}

void	flood_fill(char **tab, t_vars *vars, t_point begin)
{
	f_fill(tab, vars, tab[begin.x][begin.y], begin);
}
