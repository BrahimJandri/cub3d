/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachid <rachid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:04:23 by reddamss          #+#    #+#             */
/*   Updated: 2025/02/05 11:26:31 by rachid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Headers/cub3d_bonus.h"


void	draw_map(t_game *data)
{

    data->img->img = mlx_new_image(data->mlx, S_WIDTH, S_HEIGHT);
    if (!data->img)
        return;
    data->img->addrs = mlx_get_data_addr(data->img->img, &data->img->bpp, &data->img->size_line, &data->img->endian);

    draw_rays(data->player, data);
    data->flag = 0;
    update_minimap(data);
    render_gun(data);
    put_gun(data, data->player->frames);
    
    
    mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0,0);
    mlx_destroy_image(data->mlx, data->img->img);    
}


void    render_image(t_game *data, int wallTopPixel, int wallBottomPixel, int i)
{
   put_ceiling(data, wallTopPixel, i);
    put_wall(data, wallTopPixel, wallBottomPixel, i);
    put_floor(data, wallBottomPixel, i);
}




void draw_rays(t_player *player, t_game *data)
{
    double rayAngle;
    double angleIncrement;
    int wallTopPixel;
    int wallBottomPixel;
    int i;
    
    angleIncrement = FOV / data->num_rays;
    rayAngle = player->rotationAngle - (FOV / 2);
    i = -1;
    while(++i <  data->num_rays)
    {
        cast_rays(player, data, rayAngle);
        data->corrected_wall = data->ray->distance * cos(rayAngle - player->rotationAngle);
        data->distance_projectplan = (S_WIDTH / 2) / tan(FOV / 2);
        data->wall_projected_height = (TILE / data->corrected_wall) * data->distance_projectplan;
        wallTopPixel = (S_HEIGHT / 2) - (data->wall_projected_height / 2);
        if (wallTopPixel < 0)
            wallTopPixel = 0;
        wallBottomPixel = (S_HEIGHT / 2) + (data->wall_projected_height / 2);
        if (wallBottomPixel > S_HEIGHT)
            wallBottomPixel = S_HEIGHT;
        render_image(data, wallTopPixel, wallBottomPixel, i);
        rayAngle += angleIncrement;        
    }
}

void put_rays(t_game *data, t_player *player)
{
    double i;
    double x;
    double y;
    double j;

    i = 0;
    double rayAngle = player->rotationAngle - (FOV / 2);
    while (i < data->num_rays)
    {
        j = 0;
        while (j < 20)
        {
            x = (player->x * MINIMAP) + cos(rayAngle) * j;
            y = (player->y * MINIMAP) + sin(rayAngle) * j;
            my_mlx_pixel_put(data, x, y, LIGHT_RED);
            j++;
        }
        rayAngle += FOV / data->num_rays;
        i++;
    }
}
