/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:00:58 by peanut            #+#    #+#             */
/*   Updated: 2024/07/20 01:15:22 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	err(char *str)
{
	static int i;

	if (i)
		return (1);
	while (*str)
		write(2, str++, 1);
	i++;
	return (1);
}

t_cub	*data(void)
{
	static t_cub	data;

	return (&data);
}

void init_data(void)
{
	t_cub *d;

	d = data();
    d->mlx = NULL;
    d->win = NULL;
    d->var = (t_var){0};
    d->img = (t_img){0};
    d->color = malloc(sizeof(t_color) * 3); // Allouer de la mémoire pour les couleurs
    if (!d->color)
    {
        perror("Error allocating memory for colors");
        exit(EXIT_FAILURE);
    }
    d->map = NULL;
    d->width = 0;
    d->height = 0;
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
	data()->player = (t_player *)malloc(sizeof(t_player));
	if (data()->player == NULL)
		return (err("Malloc error for player\n"), 1);
	data()->key.esc = 0;
    data()->key.w = 0;
    data()->key.s = 0;
    data()->key.a = 0;
    data()->key.d = 0;
    data()->key.left = 0;
    data()->key.right = 0;
    data()->key.p = 1;
	return (0);
}

void	draw_ceilling_floor(void)
{
    unsigned int	*dst;
    unsigned int	i;
    int				color;
    int				color2;

    color = (data()->color->yellow.r << 16 | data()->color->yellow.g << 8 | data()->color->yellow.b);
    color2 = (data()->color->white.r << 16 | data()->color->white.g << 8 | data()->color->white.b);
    
    if (!data()->img.addr) {
        fprintf(stderr, "Error: Image data buffer is NULL\n");
        return;
    }

    dst = (unsigned int *)data()->img.addr; // Address of the image data buffer

    if (dst == NULL) {
        fprintf(stderr, "Error: Invalid image data address\n");
        return;
    }

    i = HEIGHT * WIDTH / 2 + 1;
    while (i-- > 0) {
        *dst++ = color;
    }

    i = HEIGHT * WIDTH / 2 + 1;
    while (i-- > 0) {
        *dst++ = color2;
    }
}

void	hooks(void)
{
	if (data()->key.w == 1)
	{
		ft_printf("coucou");
		player_move_forward();
	}
	if (data()->key.s == 1)
		player_move_backward();
	// if (data()->key.a == 1)
	// 	player_move_left();
	// if (data()->key.d == 1)
	// 	player_move_right();
	// if (data()->key.left == 1)
	// 	player_rotate_left();
	// if (data()->key.right == 1)
	// 	player_rotate_right();
}

int	start_the_game(void)
{
	void	*img;
	char	*addr;

	set_color();
	img = mlx_new_image(data()->mlx, WIDTH, HEIGHT);
	data()->img.pointer_to_img = img;
	addr = mlx_get_data_addr(data()->img.pointer_to_img, &data()->img.bpp, &data()->img.line_len, &data()->img.endian);
	data()->img.addr = addr;
	draw_ceilling_floor();
	raycast_loop();
	hooks();
	data()->var.frame_time = 16 / 1000.0;
	data()->var.move_speed = data()->var.frame_time * 5.0;
	mlx_put_image_to_window(data()->mlx, data()->win, img, 0, 0);
	mlx_destroy_image(data()->mlx, data()->img.pointer_to_img);
	return (0);
}

int	check_format(char *av, char *format)
{
	if (av[0] && av[0] == '.')
		av++;
	while (*av && *av != '.')
		av++;
	if (*av && *av == '.')
	{
		av++;
		if (!ft_strncmp(av, format, 4))
			return (0);
	}
	return (1);
}

char	*get_path(char *line)
{
	char 	**tmp;
	char	*tmp2;
	int		test;

	tmp = ft_split(line, ' ');
	if (!tmp)
		return (NULL);
	tmp2 = ft_strdup(tmp[1]);
    free(tmp[0]);
	free(tmp);
	if (check_format(tmp2, "xpm"))
		return (free(tmp2), err("Error, not xpm file\n"), NULL);
	test = open(tmp2, O_RDONLY);
	if (test == -1)
		return (err("Error, cannot access to the xpm file\n"), free(tmp2), NULL);
	close (test);
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
        return (0);
    new->type = type;
    new->val = get_path(line);
	if (new->val == NULL)
		return (0);
    new->next = NULL;
    add_xpm(&(data()->xpm), new);
    return (1);
}

t_rgb	*get_color(char *line)
{
	char	**tmp;
	char	**tmp2;
	t_rgb	*value;

	value = (t_rgb *)malloc(sizeof(t_rgb));
	if (!value)
		return (NULL);
	tmp = ft_split(line, ' ');
	if (!tmp)
		return (NULL);
	tmp2 = ft_split(tmp[1], ',');
	if (!tmp2)
		return (NULL);
	value->r = ft_atoi(tmp2[0]);
	value->g = ft_atoi(tmp2[1]);
	value->b = ft_atoi(tmp2[2]);
    free(tmp[0]);
    free(tmp);
    free(tmp2[0]);
    free(tmp2[1]);
    free(tmp2[2]);
    free(tmp2);
	return (value);
}

int	fill_rgb(char *line, char id)
{
	if (data()->rgb == NULL)
	{
		data()->rgb = (t_color *)malloc(sizeof(t_color));
		if (data()->rgb == NULL)
			return (err("Malloc error\n"), 0);
	}
	if (id == 'c')
		return (data()->rgb->c = get_color(line), 5);
	else
		return (data()->rgb->f = get_color(line), 6);
	return (1);
}


int check_order(char *line)
{
    static int i;

    if (i == 0 && !ft_strncmp(line, "NO", ft_strlen("NO")))
        return (++i, fill_xpm(line, E_NO));
    else if (i == 1 && !ft_strncmp(line, "SO", ft_strlen("SO")))
        return (++i, fill_xpm(line, E_SO));
    else if (i == 2 && !ft_strncmp(line, "WE", ft_strlen("WE")))
        return (++i, fill_xpm(line, E_WE));
    else if (i == 3 && !ft_strncmp(line, "EA", ft_strlen("EA")))
        return (++i, fill_xpm(line, E_EA), ++i);
    else if (i == 4 && line[0] == 'C')
        return (++i, fill_rgb(line, 'c'));
    else if (i == 5 && line[0] == 'F')
        return (++i, fill_rgb(line, 'f'));
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
            return (free(tmp), free(line), 1);
		else if (status == 6)
            return (free(tmp), free(line), 0);
        free(tmp);
        free(line);
        line = get_next_line(fd);
    }
    return (1);
}

void	free_memory(void ***str)
{
	int	i;

	i = 0;
	if (!*str)
		return ;
	while ((*str)[i])
	{
		free((*str)[i]);
		i++;
	}
	free(*str);
	*str = NULL;
}

void	big_free(void)
{
	free_memory((void ***)&data()->xpm);
	free_memory((void ***)&data()->rgb);
	free_memory((void ***)&data()->map);
}

char	**ft_realloc(char **map, int len)
{
	int		i;
	char	**new;

	i = -1;
	new = malloc(sizeof(char *) * len);
	if (!new)
		return (NULL);
	while (map[++i])
		new[i] = map[i];
	new[i] = NULL;
	new[i + 1] = NULL;
	return (free(map), new);
}

int	ft_arr_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int	add_new_line(char *line)
{
	char	**tmp;
	int		arr_len;

	arr_len = ft_arr_len(data()->map);
	if (!arr_len)
		return (1);
	tmp = ft_realloc(data()->map, arr_len + 2);
	if (!tmp)
		return (big_free(), 1);
	data()->map = tmp;
	data()->map[arr_len] = ft_strdup(line);
	if (!data()->map[arr_len])
		return (big_free(), 1);
	return (0);
}

int	fill_map(char *line)
{
	if (!data()->map)
	{
		data()->map = malloc(sizeof(char *) * 2);
		if (!data()->map)
			return (1);
		data()->map[0] = ft_strdup(line);
		if (!data()->map[0])
			return (1);
		data()->map[1] = NULL;
	}
	else
		if (add_new_line(line))
			return (1);
	return (0);
}

int	get_map(int fd)
{
	char	*line;
	char	*tmp;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		tmp = ft_strtrim(line, " \f\n\r\t\v");
		if (ft_strlen(tmp) > 0)
			if (fill_map(line))
				return (1);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	data()->height = i;
	return (0);
}

int	ft_find_edge(int i)
{
	int j;

	j = 0;
	while (data()->map[i][j] && data()->map[i][j] != '\n')
		j++;
	j--;
	while (data()->map[i][j] == ' ')
		j--;
	return (j);
}

int	control_the_edge(int i, int j)
{
	int	count;
	int	edge;

	count = 0;
	edge = ft_find_edge(i);
	while (data()->map[i][j] && data()->map[i][j] != '\n')
	{
		if (data()->map[i][j] == ' ' && count == 0)
			j++;
		else
		{
			count++;
			if (data()->map[i][j] != '1' && count == 1)
				return (0);
		}
		j++;
	}
	if (data()->map[i][edge] != '1')
		return (0);
	return (1);
}

int	check_border(int i)
{
	int	j;

	j = 0;
	if (i == 0 || i == data()->height)
	{
		while (data()->map[i][j] && data()->map[i][j] != '\n')
		{
			if (data()->map[i][j] != '1' && data()->map[i][j] != ' ')
				return (0);
			j++;
		}
	}
	else
		if (!control_the_edge(i, j))
			return (0);
	return (1);
}

int	check_data_map(int i)
{
	int	j;

	j = 0;
	while (data()->map[i][j] && data()->map[i][j] != '\n')
	{
		if (!ft_strchr(" 10NSEW", data()->map[i][j]))
			return (0);
		j++;
	}
	return (1);
}

int	check_map(void)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	count = 0;
	while (data()->map[++i])
	{
		if (!check_border(i) || !check_data_map(i))
			return (0);
		j = -1;
		while (data()->map[i][++j])
		{
			if (data()->map[i][j] == 'N' || data()->map[i][j] == 'S'
				|| data()->map[i][j] == 'E' || data()->map[i][j] == 'W')
			{
				init_vectors(i, j);
				count++;
			}
		}
	}
	if (count > 1)
		return (0);
	return (count);
}

int	parser(char *av)
{
	int	fd;

	if (check_format(av, "cub"))
		return(err("Error, wrong file format\n"));
	fd = open(av, O_RDONLY);
	if (fd == -1)
		return(close(fd), err("Error, cannot open the map\n"));
	if (get_info(fd))
		return (err("Error, wrong information\n"));
	if (get_map(fd))
		return (close(fd), err("Error, wrong map\n"));
	if (!check_map())
		return (close(fd), err("Error, the map is not well formated !"));
	return (close(fd), 0);
}

int	close_win(void)
{
	int	x;

	x = 0;
	while (x < data()->height)
	{
		free(data()->map[x]);
		x++;
	}
	free(data()->map);
	mlx_destroy_window(data()->mlx, data()->win);
	// mlx_destroy_image(data()->mlx, data()->img.pointer_to_img);
	mlx_destroy_display(data()->mlx);
	// free(data()->mlx);
	exit(0);
}

int	key_press(int keycode)
{
	 printf("Key pressed: %d\n", keycode);
	if (keycode == ESC)
		return (close_win(), 0);
	else if (keycode == W)
		data()->key.w = 1;
	else if (keycode == S)
		data()->key.s = 1;
	else if (keycode == A)
		data()->key.a = 1;
	else if (keycode == D)
		data()->key.d = 1;
	else if (keycode == LEFT)
		data()->key.left = 1;
	else if (keycode == RIGHT)
		data()->key.right = 1;
	return (0);
}

int key_release(int keycode)
{
    // Affiche le code de la touche relâchée
    printf("Key released:\n");

    // if (keycode == ESC)
    //     data()->key.esc = 0;
    if (keycode == W)
        data()->key.w = 0;
    else if (keycode == S)
        data()->key.s = 0;
    else if (keycode == A)
        data()->key.a = 0;
    else if (keycode == D)
        data()->key.d = 0;
    else if (keycode == LEFT)
        data()->key.left = 0;
    else if (keycode == RIGHT)
        data()->key.right = 0;

    return (0);
}

int main(int ac, char **av)
{
	if (ac != 2)
		return (err("Error, Map isn't correct\n"), 1);
	(void)av;
	if (init())
		return (1);
	// init_data();
	if (parser(av[1]))
		return (1);
	mlx_loop_hook(data()->mlx, start_the_game, NULL);
	mlx_hook(data()->win, PRESS, (1L << 0), &key_press, NULL);
	// mlx_hook(data()->win, ESC, (1L << 3), &close_win, NULL);
	mlx_hook(data()->win, RELEASE, (1L << 1), &key_release, NULL);
	mlx_loop(data()->mlx);
	big_free();
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