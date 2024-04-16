/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:09:37 by sung-hle          #+#    #+#             */
/*   Updated: 2023/05/29 16:33:51 by sung-hle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
enemy:
pics_init
valid_chars
print_map
set_depth
ft_hook

enums norm-check
"steps" mit NULL initialisieren? vor ausgabe und img to window und delete?
*/

#ifndef SO_LONG_H
# define SO_LONG_H
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <string.h>
# include <time.h>
# include "so_long.h"
# include "libft/libft.h"
# include "./MLX42/include/MLX42/MLX42.h"
# define IMGSIZE 64

# define L_TRASH -1
# define L_GROUND 0
# define L_WALL 1
# define L_COLLECTIBLE 2
# define L_EXIT 3
# define L_PLAYER 4

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_blink
{
	mlx_image_t	*a;
	mlx_image_t	*b;
}	t_blink;

typedef struct s_vars
{
	int			p_ctr;
	int			e_ctr;
	int			c_ctr;
	int			size_x;
	int			size_y;
	int			steps;
	int			win_lose_flag;
	char		**map;
	mlx_t		*mlx;
	t_point		start;
	t_point		exit;
	mlx_image_t	*player;
	mlx_image_t	*ground;
	mlx_image_t	*wall;
	mlx_image_t	*coll;
	mlx_image_t	*gameexit;
	mlx_image_t	*open;
}	t_vars;

/*error_checks.c*/
int				valid_chars(t_vars *vars, int i);
int				invalid_path(t_vars *vars, int i);
int				error_check(t_vars *vars, int i);
void			flood_fill(char **tab, t_vars *vars, t_point begin);
void			f_fill(char **tab, t_vars *vars, char target, t_point begin);
/*functions_two.c*/
int				return_free_split(char **map, char *s);
int				line_check(t_vars *vars, int i);
int				same_length(t_vars *vars, int i);
char			**dup_string_arr(char **original, int length);
int				which_instance(t_vars *vars);
/*functions.c*/
char			*join_and_free(char *a, char *b);
char			*check_suffix(char *str);
char			*read_file(char *argv, int *i);
void			ft_free(char **str);
int				ft_error_sl(char *s);
/*main.c*/
void			ft_so_long_init(t_vars *vars, int i);
int				terminate_level(t_vars *vars, int ret);
int				levels(int argc, char **argv, t_vars *vars);
int				init_endscreen(int flag);
/*mlx_func_two.c*/
void			set_image_depth(mlx_image_t *image, int z);
int				checker_wall(t_vars *vars, mlx_image_t *pic, int i, int dir);
int				checker_collectible(t_vars *vars);
void			blinky_player(t_vars *vars);
void			blinky_enemy(t_vars *vars);
/*mlx_func.c*/
void			win_func(t_vars *vars);
void			change_textures(t_vars *vars, mlx_image_t *a, mlx_image_t *b);
void			key_stuff(mlx_key_data_t keydata, t_vars *vars);
void			my_key_func(mlx_key_data_t keydata, void *bla);
void			ft_hook(void *vars);
/*pics.c*/
mlx_image_t		*source_to_mlx_image_t(mlx_t *mlx, char *adress);
int				pics_init_one(t_vars *vars);
int				pics_init_two(t_vars *vars);
int				pics_init_three(t_vars *vars);
int				start_and_error(int argc, char **argv, t_vars *vars);
/*print.c*/
int				print_ground(t_vars *vars);
int				print_p(t_vars *vars, int xs, int ys);
int				print_c_x_e(t_vars *vars, int xs, int ys);
int				print_img(t_vars *vars, int xs, int ys);
int				print_map(t_vars *vars);
/*some_utils.c*/
int				check_lines(char *joined);
int				cnt_maplines(char **map);
int				lose_func(t_vars *vars, int i);
int				enemies(t_vars *vars);
int				setting_ctrs(t_vars *vars, int j, int k, char c);
/*sl_bonus.c*/
int				level_up(t_vars *vars, char **lev2, char **lev3);
int				terminate(t_vars *vars, int ret);
void			my_key_func2(mlx_key_data_t keydata, void *bla);
void			ft_hook2(void *vars);
void			set_depth(t_vars *vars);
#endif