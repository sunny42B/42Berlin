/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 09:06:53 by fhassoun          #+#    #+#             */
/*   Updated: 2023/09/19 13:33:54 by sung-hle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

# define WIDTH 512
# define HEIGHT 512
# define IMG 64

# define MLX_SYNC_IMAGE_WRITABLE 1
# define MLX_SYNC_WIN_FLUSH_CMD 2
# define MLX_SYNC_WIN_CMD_COMPLETED 3

// # define mapWidth 24
// # define mapHeight 24
# define TEXWIDTH 64
# define TEXHEIGHT 64
# define SCREENWIDTH 640
# define SCREENHEIGHT 448

typedef struct s_point
{
	int				x;
	int				y;
	int				flag;
}					t_point;

typedef struct s_config
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	int				spawn_dir;
	int				spawn_x;
	int				spawn_y;
	int				f;
	int				c;
	int				map_width;
	int				map_height;
	int				map_w;
	int				map_h;
	char			**map;
	int				**maps;
}					t_config;

typedef struct s_pic
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_pic;

typedef struct s_data
{
	double			camera_x;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			olddir_x;
	double			plane_x;
	double			plane_y;
	double			oldplane_x;
	double			time;
	double			oldtime;
	double			raydir_x;
	double			raydir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				tex_num;
	double			wall_x;
	int				tex_x;
	int				tex_y;
	double			step;
	double			tex_pos;
	uint32_t		color;
	int				x;
	int				y;
	double			move_speed;
	double			rot_speed;
	double			frame_time;
	float			raydir_x0;
	float			raydir_y0;
	float			raydir_x1;
	float			raydir_y1;
	int				p;
	float			pos_z;
	float			row_distance;
	float			floor_x;
	float			floor_y;
	float			floorstep_x;
	float			floorstep_y;
}					t_data;

typedef struct s_cub
{
	mlx_t			*mlx;
	t_config		*config;
	t_data			data;
	mlx_image_t		*pic[2];
	mlx_image_t		*fps_pic;
	unsigned int	buffer[SCREENHEIGHT][SCREENWIDTH];
	int				**texture;
	xpm_t			*tex0;
	xpm_t			*tex1;
	xpm_t			*tex2;
	xpm_t			*tex3;
}					t_cub;

/*
** main.c
*/
void				error_message(char *error_message);
void				error(void);
void				ft_hook(void *param);
int					get_color_from_pixel(uint8_t *pixel);

/*
** texturs.c
*/
int					create_textures(t_cub *cub);

/*
** texture_utils.c
*/
void				load_greystone(t_cub *cub);
void				load_mossy(t_cub *cub);
void				load_purplestone(t_cub *cub);
void				load_redbrick(t_cub *cub);
void				load_wood(t_cub *cub);

/*
** routine.c
*/
void				routine(void *test);

// error_handling.c
char				*join_and_free(char *a, char *b);
char				*check_suffix(char *str);
char				*read_file(char *argv, int *i);
int					is_map(char chr);
int					is_player(char chr);

// error_handling2.c
int					ft_config_init(t_cub *cub);
char				**dup_map(t_cub *cub, char **original);
int					convert_map(t_cub *cub, char **map);
void				free_int_map(int **arr, int i);
void				fill_int_arr(t_cub *cub, char **map, int i);

// main.c
uint32_t			ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
int					error_check(t_cub *cub, char *joined);
int					start_and_error(int argc, char **argv, t_cub *cub);
// int		error_check(t_cub *cub, char *joined);
// int		start_and_error(int argc, char **argv, t_cub *cub);

// parse_config.c
int					set_path(char **conf, char *identifier, char *split_i);
int					check_and_get_color(char **ff, char identifier);
int					set_color(int *conf, char identifier, char *split_i);
int					set_map(char **split, int *i, t_list **head);
int					ft_fill_config(t_cub *cub, char **split, t_list **head,
						int *flag);

// print_funcs.c
void				print_after_read_list(t_cub *cub, t_list *head);
void				print_map(char **map);
void				print_config(t_cub *cub);
void				print_int_arr_plus(t_cub *cub);

// parse_map.c
int					get_map_arr(t_cub *cub, t_list *head);
int					get_map(t_cub *cub, t_list *head);
int					parse_map(t_cub *cub, char **split);

// wall_check.c
int					check_surroundings(char **map, int i, int j);
int					check_zeros(char **map);
int					get_start_pos(char **dup, t_point *start);
int					wall_check(t_cub *cub, char **map);

// free_and_error.c
int					ft_error_sl(char *s);
void				free_the_shit(t_cub *cub);
void				free_int_two_d(t_cub *cub);
int					free_paths(char **path);
int					free_config(t_cub *cub, t_list *head);

// free_and_error2.c
void				error_message(char *error_message);
void				error(void);
int					error_check(t_cub *cub, char *joined);
int					start_and_error(int argc, char **argv, t_cub *cub);
void				free_texture(t_cub *cub);

// error_checks.c
int					line_check(t_cub *cub, char *joined);
int					valid_chars(char **map);
int					f_fill_out(char **tab, t_point pt);
void				f_fill(char **tab, t_cub *cub, int *flag, t_point begin);
void				flood_fill(char **tab, t_cub *cub, int *flag,
						t_point begin);

// movement.c
void				movement(t_cub *cub);

// movement_utils.c
void				move_forward(t_cub *cub);
void				move_backward(t_cub *cub);
void				move_left(t_cub *cub);
void				move_right(t_cub *cub);

// floor_casting.c
void				floor_casting_calculations(t_cub *cub, int y);
void				floor_casting(t_cub *cub);

//wall_casting.c
void				wall_casting(t_cub *cub);
void				initial_calculations(t_cub *cub, int x);

//wall_casting_utils.c
void				initial_calculations(t_cub *cub, int x);
void				calculate_step_and_sidedist(t_cub *cub);
void				perform_dda(t_cub *cub);
void				calculate_camera_distance(t_cub *cub);
void				calc_height_and_pix(t_cub *cub);

#endif