/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:00:58 by peanut            #+#    #+#             */
/*   Updated: 2024/07/16 14:30:23 by skapersk         ###   ########.fr       */
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

char	*get_path(char *line)
{
	char 	**tmp;
	char	*tmp2;

	tmp = ft_split(line, ' ');
	if (!tmp)
		return (NULL);
	tmp2 = ft_strdup(tmp[1]);
    // while (*tmp)
    // {
    //     free(*tmp);
    //     tmp++;
    // }
    free(tmp[0]);
	return (tmp2);
}

void add_xpm(t_xpm **lst, t_xpm *new)
{
    t_xpm *current;

    if (*lst == NULL)
    {
        *lst = new;
        return;
    }
    current = *lst;
    while (current->next != NULL)
        current = current->next;
    current->next = new;
}

int fill_xpm(char *line, t_type_xpm type)
{
    t_xpm *new;

    new = (t_xpm *)malloc(sizeof(t_xpm));
    if (!new)
        return (1);
    new->type = type;
    new->val = get_path(line);
    new->next = NULL;
    add_xpm(&(data()->xpm), new);
    return (0);
}

int check_order(char *line)
{
    static int i;

    if (i == 0 && !ft_strncmp(line, "NO", ft_strlen("NO")))
        return (fill_xpm(line, E_NO), ++i);
    else if (i == 1 && !ft_strncmp(line, "SO", ft_strlen("SO")))
        return (fill_xpm(line, E_SO), ++i);
    else if (i == 2 && !ft_strncmp(line, "WE", ft_strlen("WE")))
        return (fill_xpm(line, E_WE), ++i);
    else if (i == 3 && !ft_strncmp(line, "EA", ft_strlen("EA")))
        return (fill_xpm(line, E_EA), ++i);
    else if (i == 4 && line[0] == 'C')
    {
        // fill_rgb(line);
        return (++i);
    }
    else if (i == 5 && line[0] == 'F')
    {
        // fill_rgb(line);
        return (++i);
    }
    else if (!ft_strncmp(line, "", ft_strlen ("")))
        return (1);
	else if (line[0] == 'F' || line[0] == 'C' || !ft_strncmp(line, "EA", ft_strlen("EA"))
		|| !ft_strncmp(line, "WE", ft_strlen("WE")) || !ft_strncmp(line, "SO", ft_strlen("SO"))
		|| !ft_strncmp(line, "NO", ft_strlen("NO")))
			return (0);
	return (0);
}

int get_info(int fd)
{
    char *line;
    char *tmp;
	int	status;

    line = get_next_line(fd);
    while (line)
    {
        tmp = ft_strtrim(line, " \f\n\r\t\v");
        status = check_order(tmp);
		if (!status)
        {
            free(tmp);
            free(line);
            return (1);
        }
		else if (status == 6)
        {
            free(tmp);
            free(line);
            return (0);
        }
        free(tmp);
        free(line);
        line = get_next_line(fd);
    }
    return (1);
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
	// if (get_map(fd))
	// 	return (err("Error, wrong map\n"));
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