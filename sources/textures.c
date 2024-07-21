/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 21:41:46 by skapersk          #+#    #+#             */
/*   Updated: 2024/07/21 22:15:22 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#include "cub3d.h"

void fill_img2_with_textures(int i)
{
    int x;
    int y;
	int *addr;

    addr = (int *)(data()->img2[i].addr); 
    x = 0;
    while (x < data()->img2[i].height)
    {
        y = 0;
        while (y < data()->img2[i].width)
        {
            data()->textures[i][data()->img2[i].width * x + y] = addr[data()->img2[i].width * x + y];
            y++;
        }
        x++;
    }
}

int init_textures(void)
{
    int i;
    void *tmp;
    int *addr;

    i = 0;
    while (i < 4)
    {
        tmp = mlx_xpm_file_to_image(data()->mlx, data()->xpm->val,
                                    &(data()->img2[i].width), &(data()->img2[i].height));
        if (!tmp)
            return (1);
        data()->img2[i].pointer_to_img = tmp;
        addr = (int *)mlx_get_data_addr(data()->img2[i].pointer_to_img,
                                        &data()->img2[i].bpp, &data()->img2[i].line_len,
                                        &data()->img2[i].endian);
        if (!addr)
            return (1);
        data()->img2[i].addr = addr;
        fill_img2_with_textures(i);
        mlx_destroy_image(data()->mlx, data()->img2[i].pointer_to_img);
		data()->xpm = data()->xpm->next;
        i++;
    }
    return (0);
}
