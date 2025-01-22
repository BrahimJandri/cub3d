/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_walls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachid <rachid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:50:53 by rachid            #+#    #+#             */
/*   Updated: 2025/01/22 10:42:31 by rachid           ###   ########.fr       */
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

int	apply_shadow(int color, double shadow_factor)
{
	int	r;
	int	g;
	int	b;

	r = color >> 16 & 0xFF;
	g = color >> 8 & 0xFF;
	b = color & 0xFF;
	r = (int)(r * shadow_factor);
	g = (int)(g * shadow_factor);
	b = (int)(b * shadow_factor);
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return (r << 16 | (g << 8) | b);
}

int	shade_walls(int color, double distance)
{
	double	ambient_light;
	double	shadow_factor;

	ambient_light = 0.5;
	shadow_factor = fmax(ambient_light, 1.0 / (distance + 1.0));
	return (apply_shadow(color, shadow_factor));
}