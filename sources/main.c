/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:00:58 by peanut            #+#    #+#             */
/*   Updated: 2024/07/14 18:40:34 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	err(char *str)
{
	while (*str)
		write(2, str++, 1);
	return (1);
}

t_cub	*data(void)
{
	static t_cub	data;

	return (&data);
}

void	init(void)
{
	void	*tmp;

	data()->mlx = mlx_init();
	tmp = mlx_new_window(data()->mlx, WIDTH, HEIGHT, "cub3D");
	data()->
}

int main(int ac, char **av)	// main function
{
	if (ac != 2)
		return (err("Error : Map isn't correct\n"), 1);
	// parse(av(1));
	init();	// init the data structure
	start_the_game(data);	// start the game
	return 0;
}

// t_cub	*data(void)
// {
// 	static t_cub	data;

// 	return (&data);
// }

// void	ft_exit(t_mlx *mlx) 		// exit the game
// {
// 	int	i = 0;
// 	while (mlx->dt->map2d[i])
// 		free(mlx->dt->map2d[i++]); // free the map line by line
// 	free(mlx->dt->map2d); // free the map
// 	free(mlx->dt); // free the data structure
// 	free(mlx->ply); // free the player structure
// 	free(mlx->ray); // free the ray structure
// 	mlx_delete_image(mlx->mlx_p, mlx->img); // delete the image
// 	mlx_close_window(mlx->mlx_p); // close the window
// 	mlx_terminate(mlx->mlx_p); // terminate the mlx pointer
// 	printf("Game closed\n"); // print the message
// 	exit(0); // exit the game
// }

// int mlx_key(int keycode, t_mlx *mlx)
// {
//     // Votre code de gestion des touches ici
// 	(void)keycode; // Indique que keycode n'est pas utilisé
//     (void)mlx; 
//     return (0);
// }

// void	hook(t_mlx *mlx, double move_x, double move_y)	// hook the player
// {
// 	if (mlx->ply->rot == 1) //rotate right
// 		rotate_player(mlx, 1);
// 	if (mlx->ply->rot == -1) //rotate left
// 		rotate_player(mlx, 0);
// 	if (mlx->ply->l_r == 1) //move right
// 	{
// 		move_x = -sin(mlx->ply->angle) * PLAYER_SPEED;
// 		move_y = cos(mlx->ply->angle) * PLAYER_SPEED;
// 	}
// 	if (mlx->ply->l_r == -1) //move left
// 	{
// 		move_x = sin(mlx->ply->angle) * PLAYER_SPEED;
// 		move_y = -cos(mlx->ply->angle) * PLAYER_SPEED;
// 	}
// 	if (mlx->ply->u_d == 1) //move up
// 	{
// 		move_x = cos(mlx->ply->angle) * PLAYER_SPEED;
// 		move_y = sin(mlx->ply->angle) * PLAYER_SPEED;
// 	}
// 	if (mlx->ply->u_d == -1) //move down
// 	{
// 		move_x = -cos(mlx->ply->angle) * PLAYER_SPEED;
// 		move_y = -sin(mlx->ply->angle) * PLAYER_SPEED;
// 	}
// 	move_player(mlx, move_x, move_y); // move the player
// }

// void	cast_rays(t_mlx *mlx)	// cast the rays
// {
// 	double	h_inter;
// 	double	v_inter;
// 	int		ray;

// 	ray = 0;
// 	mlx->ray->ray_ngl = mlx->ply->angle - (mlx->ply->fov_rd / 2); // the start angle
// 	while (ray < S_W) // loop for the rays
// 	{
// 		mlx->ray->flag = 0; // flag for the wall
// 		h_inter = get_h_inter(mlx, nor_angle(mlx->ray->ray_ngl)); // get the horizontal intersection
// 		v_inter = get_v_inter(mlx, nor_angle(mlx->ray->ray_ngl)); // get the vertical intersection
// 		if (v_inter <= h_inter) // check the distance
// 			mlx->ray->distance = v_inter; // get the distance
// 		else
// 		{
// 			mlx->ray->distance = h_inter; // get the distance
// 			mlx->ray->flag = 1; // flag for the wall
// 		}
// 		render_wall(mlx, ray); // render the wall
// 		ray++; // next ray
// 		mlx->ray->ray_ngl += (mlx->ply->fov_rd / S_W); // next angle
// 	}
// }

// int game_loop(void *ml) // game loop
// {
//     t_mlx *mlx;

//     mlx = ml; // cast to the mlx structure
//     // mlx_destroy_image(mlx->mlx_p, mlx->img); // delete the image
//     mlx->img = mlx_new_image(mlx->mlx_p, WIDTH, HEIGHT); // create new image
//     hook(mlx, 0, 0); // hook the player
//     cast_rays(mlx); // cast the rays
//     mlx_put_image_to_window(mlx->mlx_p, mlx->win, mlx->img, 0, 0); // put the image to the window
//     return (0); // Ajoutez un retour de type int
// }

// void init_the_player(t_mlx mlx) // init the player structure
// {
// 	mlx.ply->plyr_x = mlx.dt->p_x * TILE_SIZE + TILE_SIZE / 2;
// 	mlx.ply->plyr_y = mlx.dt->p_y * TILE_SIZE + TILE_SIZE / 2;
// 	mlx.ply->fov_rd = (FOV * M_PI) / 180;
// 	mlx.ply->angle = M_PI;
// }

// void	start_game(t_cub *dt) // start the game
// {
// 	t_mlx	mlx;

// 	mlx.dt = dt; // init the mlx structure
// 	mlx.ply = calloc(1, sizeof(t_player)); // init the player structure i'm using calloc to initialize the variables to zero
// 	mlx.ray = calloc(1, sizeof(t_ray)); // init the ray structure
// 	mlx.mlx_p = mlx_init(WIDTH, HEIGHT, "Cub3D", 0); // init the mlx pointer and put a window to the screen
// 	init_the_player(mlx); // init the player structure
// 	mlx_loop_hook(mlx.mlx_p, &game_loop, &mlx); // game loop continuously call a specified function to update the game state and render the frames.
// 	mlx_key_hook(mlx.mlx_p, &mlx_key, &mlx); // key press and release
// 	mlx_loop(mlx.mlx_p); // mlx loop
// 	ft_exit(&mlx); // exit the game
// }

// t_cub	*init(void)
// {
// 	t_cub	*data;

// 	data = calloc(1, sizeof(t_cub));
// 	data->map2d = calloc(10, sizeof(char *));
// 	data->map2d[0] = ft_strdup("1111111111111111111111111");
// 	data->map2d[1] = ft_strdup("1000000000000000000100001");
// 	data->map2d[2] = ft_strdup("1001000000000P00000000001");
// 	data->map2d[3] = ft_strdup("1001000000000000001000001");
// 	data->map2d[4] = ft_strdup("1001000000000000001000001");
// 	data->map2d[5] = ft_strdup("1001000000100000001000001");
// 	data->map2d[6] = ft_strdup("1001000000000000001000001");
// 	data->map2d[7] = ft_strdup("1001000000001000001000001");
// 	data->map2d[8] = ft_strdup("1111111111111111111111111");
// 	data->map2d[9] = NULL;
// 	data->p_y = 3; // player y position in the map
// 	data->p_x = 14; // player x position in the map
// 	data->w_map = 25; // map width
// 	data->h_map = 9; // map height
// 	return (data); // return the data structure
// }

// int	main(void)
// {
// 	t_cub	*data;

// 	data = init();
// 	start_game(data);
// 	return (0);
// }

// int main(void)
// {
//     void    *mlx;
//     void    *mlx_win;
//     void	*img;
// 	char	*relative_path = "./assets/Trip3.xpm";
// 	int		img_width;
// 	int		img_height;

//     mlx = mlx_init();
//     mlx_win = mlx_new_window(mlx, 1920, 1000, "cub3D");
//     img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
//     if (img == NULL)
//     {
//         fprintf(stderr, "Erreur : Impossible de charger l'image %s\n", relative_path);
//         return (1);
//     }
//     mlx_put_image_to_window(mlx, mlx_win, img, 0, 0);
//     mlx_loop(mlx);
// }