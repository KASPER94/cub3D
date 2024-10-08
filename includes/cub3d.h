/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:53:17 by peanut            #+#    #+#             */
/*   Updated: 2024/09/04 16:47:01 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "../minilibx/mlx.h"
# include <stdio.h>
# include "../libft/INCLUDES/libft.h"
# include <X11/keysym.h>
# include <sys/time.h>

# define _USE_MATH_DEFINES

# define WIDTH 950 // screen width
# define HEIGHT 500 // screen height
# define FOV 66 // field of view
# define ROTATION_SPEED 1.0 // rotation speed
# define PLAYER_SPEED 2.5 // player speed
# define MOUSE_SENSI 2.5 // mouse sensitivity

# define PRESS		2
# define RELEASE	3

# define TEXTURE_HEIGHT 			64
# define TEXTURE_WIDTH 				64

//french keyboard
// # define W 						122
// # define A 						113
// # define S 						115
// # define D 						100

# define W 						119
# define A						97
# define S 						115
# define D 						100
# define UP 					126
# define DOWN 					125
# define LEFT 					65361
# define RIGHT 					65363
# define ESC 		65307

typedef struct s_player
{
	int		p_x;
	int		p_y;
	char	dir;
}	t_player;

typedef struct s_coordinate
{
	int		x;
	int		y;
	t_bool	visited;
}	t_coordinate;

typedef enum e_type_xpm
{
	E_NO,
	E_SO,
	E_WE,
	E_EA
}	t_type_xpm;

typedef struct s_img
{
	void		*pointer_to_img;
	void		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			width;
	int			height;
	t_type_xpm	type;
}	t_img;

typedef struct s_xpm
{
	char			*val;
	t_type_xpm		type;
	struct s_xpm	*next;
}	t_xpm;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_color
{
	t_rgb	*c;
	t_rgb	*f;
}	t_color;

typedef struct s_map
{
	int	r;
	int	l;
}	t_map;

typedef struct s_var
{
	double	camera;
	double	ray_dir_x;
	double	ray_dir_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	position_x;
	double	position_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	double	move_speed;
	double	frame_time;
	double	old_time;
	double	rot_speed;
	double	test;
	double	step;
	double	wall;
	double	texture_position;
	int		hit;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		texture_number;
	int		texture_y;
	int		texture_x;
	int		color;
	int		tex;
	double	run;
}	t_var;

typedef struct s_test_color
{
	t_rgb	blue;
	t_rgb	red;
	t_rgb	green;
	t_rgb	white;
	t_rgb	yellow;
}	t_test_color;

typedef struct s_key
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	right;
	int	left;
	int	p;
	int	esc;
	int	run;
}				t_key;

typedef struct s_cub
{
	void			*mlx;
	void			*win;
	t_xpm			*xpm;
	t_color			rgb;
	char			**map;
	int				height;
	int				width;
	t_img			img;
	t_img			img2[4];
	t_img			txt;
	int				textures[4][TEXTURE_HEIGHT * TEXTURE_WIDTH];
	t_player		*player;
	t_var			var;
	t_test_color	color;
	t_key			key;
	int				map_height;
	int				map_width;
	t_map			edge;
	int				mouse;
	double			mouse_pan_x;
	double			mouse_pan_y;
}	t_cub;

int				raycast_loop(void);
void			init_vectors(int x, int y);
t_cub			*data(void);
void			set_color(void);
void			player_move_left(void);
void			player_move_forward(void);
void			player_move_backward(void);
void			player_rot_left(void);
void			player_rot_right(void);
void			player_move_right(void);
int				init_textures(void);

// main.c

int				fill_rgb(char **split, char id);
int				ft_arr_len(char **array);
char			**ft_realloc(char **map, int len);
int				clean_exit(void);

// check_around.c

t_bool			check_right(t_coordinate p, char	**map);
t_bool			check_left(t_coordinate p, char	**map);
t_bool			check_under(t_coordinate p, char	**map);
t_bool			check_top(t_coordinate p, char	**map);

// check_map.c

int				check_map(void);
t_coordinate	init_coordinate(int x, int y);

// clean.c

void			destroy_xpm(void);
void			destroy_map(void);
void			destroy_imgs(void);
void			destroy_colors(void);
int				clean_exit(void);

// color_utils.c

int				check_colors(char **colors);

// color.c

int				check_len(char **tmp);

// draw.c

void			set_color(void);
void			mlx_place_pixel(int x, int y, int color);
void			draw_wall(int x);
void			my_floor(int x);
void			my_cell(int x);

// error.c

int				err(char *str);

// events.c

int				key_press(int keycode);
int				key_release(int keycode);
void			hooks(void);

// init.c

int				init(void);
int				init_win(void);
void			init_data(void);
t_cub			*data(void);

// movements_rot.c

void			player_rot_left(void);
void			player_rot_right(void);

// mouvements.c

// parse_get_info.c

int				get_info(int fd);
int				split_len(char **split);
t_bool			line_is_empty(char *line);
void			destroy_xpm(void);

//parse_get_map_utils.c

int				check_end(int fd);
void			reverse_map(void);

//parse_get_map.c

int				get_map(int fd);

// parse.c

int				parser(char *filename);
int				check_format(char *filename, char *format);

// path_checker_utils.c

t_bool			not_surrounded(t_coordinate p, char	**map);
t_bool			has_been_visited(t_coordinate p, char **visited);

// path_checker.c

int				path_checker(t_coordinate start);

// raycast_loop.c

void			find_lowest_and_high_pix(void);
void			coor_text(void);
void			render_texture(int x);

// raycasting.c

void			init_vectors(int x, int y);
void			find_ray_and_dir(int x, int w);
void			dda_algo(void);
void			dist_project_camera(void);
void			set_height_wall(void);

// set_display.c

void			set_texture(void);
void			set_values(double direction_x,
					double direction_y, double pla_x, double pla_y);
void			set_box(void);
void			set_len_ray(void);
void			set_step_and_ini_side_dist(void);

// utils.c

char			**ft_realloc(char **map, int len);
int				ft_arr_len(char **array);
int				split_len(char **split);
t_bool			line_is_empty(char *line);
t_bool			is_space(int c);

// xpm.c

int				fill_xpm(char *path, t_type_xpm type);

#endif
