/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachid <rachid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:04:23 by reddamss          #+#    #+#             */
/*   Updated: 2025/01/19 00:11:26 by rachid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./Headers/cub3d.h"


void	draw_map(t_game *data)
{
    data->img = mlx_new_image(data->mlx, S_WIDTH, S_HEIGHT);  
    if(!data->img)
        return ;
    data->addrs = mlx_get_data_addr(data->img, &data->bpp, &data->size_line, &data->endian);

    draw_minimap(data);
    // draw_line(data->player, data);
    // line(data->player, data);
    draw_circle(data->player, data);
    
    draw_rays(data->player, data);
    
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0,0);
    mlx_destroy_image(data->mlx, data->img);
    // render_walls(data, data->player);
    // cast_rays(data->player, data, data->player->rotationAngle);
    
}



int get_texture_color(unsigned int *texture_data, int tex_width, int tex_height, int x, int y)
{
    // Make sure the x and y are within bounds
    if (x < 0 || x >= tex_width || y < 0 || y >= tex_height) {
        return 0; // Return black if out of bounds (or any other default color)
    }

    // Get the pixel color as an unsigned int (RGBA format)
    return texture_data[y * tex_width + x];
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void    draw_rays(t_player *player, t_game *data)
{
    double i;
    double x;
    double y;
    double j;
    
    i = 0;

    double rayAngle = player->rotationAngle - (FOV / 2);
    // cast_rays(player,data,rayAngle);

    while(i < data->num_rays)//this while fill the array of rays while changing the rayAngle
    {//
            cast_rays(player, data, rayAngle);
            j = 0;

            // draw_line(player, data, data->ray->x_hit, data->ray->y_hit);
            double      corrected_wall = data->ray->distance * cos(rayAngle - player->rotationAngle);
            double      distance_projectplan = (S_WIDTH / 2) / tan(FOV / 2);
            double      wall_projected_height = (TILE / corrected_wall) * distance_projectplan;
            
            int     WallTopPixel = (S_HEIGHT / 2) - (wall_projected_height / 2);
            if(WallTopPixel < 0)
                WallTopPixel = 0;
            int     WallBottomPixel = (S_HEIGHT / 2) + (wall_projected_height / 2);
            if(WallBottomPixel > S_HEIGHT)
                WallBottomPixel = S_HEIGHT;
    //---------------------------------------------------------------------------------
        int texture_x = (int)(rayAngle * data->tex_width / (2 * PI)) % data->tex_width;

        // Draw the textured wall slice
        for (int y = WallTopPixel; y < WallBottomPixel; y++)
        {
            // Calculate the texture Y-coordinate based on the y-position of the wall slice
            double texture_pos = (y - (S_HEIGHT / 2 - wall_projected_height / 2)) * data->tex_height / wall_projected_height;
            if (texture_pos < 0) texture_pos = 0;
            if (texture_pos >= data->tex_height) texture_pos = data->tex_height - 1;

            // Sample the color from the texture (texture data is a 1D array of pixels)
            int color = get_texture_color(data->tex_data, data->tex_width, data->tex_height, texture_x, (int)texture_pos);

            // Draw the pixel at the correct position in the window using the color from the texture
            my_mlx_pixel_put(data, i * WALL_WIDTH, y, color);
        }
    //---------------------------------------------------------------------------------

            // draw_rectangle(data, i * WALL_WIDTH, (S_HEIGHT / 2) - (wall_projected_height / 2) ,WALL_WIDTH, wall_projected_height);
            
            while(j < data->ray->distance)
            {
                x = player->x + cos(rayAngle) * j;
                y = player->y + sin(rayAngle) * j;
    
                my_mlx_pixel_put(data, x, y, RED);
                /*WHERE WE WILL RENDER THE WALL AFTER*/

                j++;
            }
            // reset_window(data,0, 0);
            // mlx_destroy_image(data->mlx);
            // draw_line(player, data, x, y);
        rayAngle += FOV / data->num_rays;
        i++;
    }

}
