/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:00:58 by peanut            #+#    #+#             */
/*   Updated: 2024/07/15 15:12:14 by skapersk         ###   ########.fr       */
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

int init(void)
{
	void *tmp;
	t_img *img_ptr;

	data()->mlx = mlx_init();
	tmp = mlx_new_window(data()->mlx, WIDTH, HEIGHT, "cub3D");
	img_ptr = (t_img *)malloc(sizeof(t_img));
	if (img_ptr == NULL)
		return (err("Malloc error\n"), 1);
	data()->img = *img_ptr;
	free(img_ptr);
	data()->win = tmp;
	return (0);
}
int	start_the_game(void)
{
	void	*img;
	char	*addr;

	img = mlx_new_image(data()->mlx, WIDTH, HEIGHT);
	data()->img.pointer_to_img = img;
	addr = mlx_get_data_addr(data()->img.pointer_to_img, &data()->img.bpp, &data()->img.line_len, &data()->img.endian);
	data()->img.addr = addr;
	
	mlx_put_image_to_window(data()->mlx, data()->win, img, 0, 0);
	return (0);
}

int	check_format(char *av)
{
	if (av[0] && av[0] == '.')
		av++;
	while (*av && *av != '.')
		av++;
	if (*av && *av == '.')
	{
		av++;
		if (!ft_strncmp(av, "cub", 4))
			return (0);
	}
	return (1);
}

int	get_info()
{
	
}

int	parser(char *av)
{
	int	fd;

	if (check_format(av))
		return(err("Error, wrong file format\n"));
	fd = open(av, O_RDONLY);
	if (fd == -1)
		return(err("Error, cannot open the map\n"));
	if (get_info(fd))
		return (err("Error, wrong information\n"));
	if (get_map(fd))
		return (err("Error, wrong map\n"));
	return (0);
}

int main(int ac, char **av)
{
	if (ac != 2)
		return (err("Error : Map isn't correct\n"), 1);
	(void)av;
	if (parser(av[1]))
		return (1);
	if (init())
		return (1);
	mlx_loop_hook(data()->mlx, start_the_game, NULL);
	mlx_loop(data()->mlx);
	return 0;
}

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