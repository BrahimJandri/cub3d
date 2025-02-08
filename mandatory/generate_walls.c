/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_walls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachid <rachid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:50:53 by rachid            #+#    #+#             */
/*   Updated: 2025/02/08 10:12:52 by rachid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Headers/cub3d.h"


//     }
// }
//here where i draw the rectange that represents walls.
//before i draw this i should reset the window to black without touching the mini-map

// void    reset_window(t_game *data)
// {
//     data->img = mlx_new_image(data->mlx, S_WIDTH, S_HEIGHT - data->map_y);
//     data->addrs = mlx_get_data_addr(data->img, data->bitppixel, data->size_line, data->endian);
    
// }


void    draw_rectangle(t_game *data, int x, int y, int width, int height)
{
    int i;
    int j;


    i = 0;
    while(i < height)
    {
        j = 0;
        while(j < width)
        {
            my_mlx_pixel_put(data, j + x, i + y, WHITE);
            j++;
        }
        i++;
    }
}

void	my_mlx_pixel_put(t_game *data, int x, int y, int color)
{
	char	*dst;
    
    if (x < 0 || x >= S_WIDTH || y < 0 || y >= S_HEIGHT) {
        return;
    }

	dst = data->img->addrs + (y * data->img->size_line + x * (data->img->bpp / 8));

	*(unsigned int*)dst = color;
}

