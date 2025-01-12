/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_walls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reddamss <reddamss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:50:53 by rachid            #+#    #+#             */
/*   Updated: 2025/01/12 11:33:00 by reddamss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Headers/cub3d.h"

// void    render_walls(t_game *data, t_player *player)
// {
//     int i;
//     double wall_projected_height;
//     double distance_projectplan;
//     i = 0;

//     while(i < data->num_rays)
//     {
//         // cast_rays(player,)

//         wall_projected_height = TILE / data->ray->distance * distance_projectplan;

//         distance_projectplan = (S_WIDTH / 2) / tan(FOV / 2);
//         draw_rectangle(data, (S_WIDTH / 2) - wall_projected_height ,WALL_WIDTH, wall_projected_height)


        
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
    // printf("x = %d, y = %d, height = %d, width = %d\n", x, y, height, width);
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
    
    
    if (x < 0 || x >= data->map_height || y < 0 || y >= data->map_width) {
        fprintf(stderr, "Error: x or y is out of bounds\n");
        return;
    }

    // printf("x=%d ,y=%d\n",x, y);
	dst = data->addrs + (y * data->size_line + x * (data->bpp / 8));

    // printf("this is the dest%s\n", dst);
	*(unsigned int*)dst = color;
}