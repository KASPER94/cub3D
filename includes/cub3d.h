/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:53:17 by peanut            #+#    #+#             */
/*   Updated: 2024/07/15 15:54:28 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
// # include <limits.h>
# include "../minilibx/mlx.h"
# include <stdio.h>
# include "../libft/INCLUDES/libft.h"

# define WIDTH 1900 // screen width
# define HEIGHT 1000 // screen height
# define TILE_SIZE 30 // tile size
# define FOV 60 // field of view
# define ROTATION_SPEED 0.045 // rotation speed
# define PLAYER_SPEED 4 // player speed

typedef struct s_player //the player structure
{
	int			plyr_x; // player x position in pixels
	int			plyr_y; // player y position in pixels
	double		angle; // player angle
	float		fov_rd; // field of view in radians
	int			rot; // rotation flag
	int			l_r; // left right flag
	int			u_d; // up down flag
}	t_player;

typedef struct s_ray //the ray structure
{
	double		ray_ngl; // ray angle
	double		distance; // distance to the wall
	int			flag; // flag for the wall
}	t_ray;

typedef struct s_data	//the data structure
{
	char	**map2d;	// the map
	int		p_x;		// player x position in the map
	int		p_y;		// player y position in the map
	int		w_map;		// map width
	int		h_map;		// map height
}	t_data;

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

typedef struct	s_xpm
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_xpm;

typedef struct	s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct	s_color
{
	t_rgb	c;
	t_rgb	f;
}	t_color;

typedef struct	s_cub
{
	void	*mlx;
	void	*win;
	t_xpm	var;
	t_rgb	rgb;
	t_img	img;
	t_img	img2[4];
}	t_cub;

#endif