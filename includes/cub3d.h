/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:53:17 by peanut            #+#    #+#             */
/*   Updated: 2024/07/25 12:03:52 by skapersk         ###   ########.fr       */
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

# define WIDTH 1900 // screen width
# define HEIGHT 1000 // screen height
# define TILE_SIZE 30 // tile size
# define FOV 60 // field of view
# define ROTATION_SPEED 0.045 // rotation speed
# define PLAYER_SPEED 4 // player speed

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

typedef struct s_img
{
	void	*pointer_to_img;
	void	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef enum e_type_xpm
{
	E_NO,
	E_SO,
	E_WE,
	E_EA
}	t_type_xpm;

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
	double	rayDirX;
	double	rayDirY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	double	position_x;
	double	position_y;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	double	move_speed;
	double	frame_time;
	double	rot_speed;
	double	test;
	double	wall;
	int		hit;
	int		mapX;
	int		mapY;
	int 	stepX;
	int 	stepY;
	int		side;
	int 	lineHeight;
	int		drawStart;
	int		drawEnd;
	int		texture_number;
	int		texture_y;
	int		texture_x;
	int		color;
	int		tex;
}	t_var;

typedef struct	s_test_color
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
}				t_key;

typedef struct s_cub
{
	void			*mlx;
	void			*win;
	t_xpm			*xpm;
	t_color			*rgb;
	char			**map;
	int				height;
	int				width;
	t_img			img;
	t_img			img2[4];
	t_img			txt;
	int				textures[4][TEXTURE_HEIGHT * TEXTURE_WIDTH];
	t_player		*player;
	t_var			var;
	t_test_color	*color;
	t_key			key;
	int				map_height;
	int				map_width;
	t_map			edge;
}	t_cub;

int		raycast_loop(void);
void	init_vectors(int x, int y);
t_cub	*data(void);
void	set_color(void);
void	player_move_forward(void);
void	player_move_backward(void);
void	player_rot_right(void);
void	player_move_left(void);
void	player_move_right(void);
int		init_textures(void);
void	player_rot_left(void);

#endif
