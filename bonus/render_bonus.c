/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachid <rachid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:04:23 by reddamss          #+#    #+#             */
/*   Updated: 2025/02/02 10:21:54 by rachid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./Headers/cub3d_bonus.h"

void    game_loop(t_game *data)
{
    get_data(data);
    draw_map(data);
    
}



void	draw_map(t_game *data)
{

    data->img->img = mlx_new_image(data->mlx, S_WIDTH, S_HEIGHT);  
    if(!data->img)
        return ;
    data->img->addrs = mlx_get_data_addr(data->img->img, &data->img->bpp, &data->img->size_line, &data->img->endian);

    draw_rays(data->player, data);
    update_minimap(data);
    render_gun(data);
    put_gun(data, data->player->frames);
    
    
    mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0,0);
    mlx_destroy_image(data->mlx, data->img->img);    
}

void    get_data(t_game *data)
{   
    if(data->player->walkDir)
    {
        update_player(data, data->player);
    }
    if(data->player->turnDir)
    {
        data->player->rotationAngle += data->player->turnDir * data->player->rotationSpeed;
    }
    if(data->player->sideDir)
    {
        update_sides(data, data->player);
    }
    return ;
}

int    get_color(t_texture *texture, int x, int y)
{
    unsigned int color;

    color = *(int *)(texture->addrs + (y * texture->size_line) + x
		* (texture->bpp / 8));
    
    return color;
} 

//array: 0 = so, 1 = no, 2 = we, 3 = ea;

void    get_the_right_color(t_game *data, int offset_x, int offset_y)
{
    if(!data->ray->is_vert && !data->ray->ray_down)
        data->color = get_color(data->texture[1], offset_x, offset_y);
        
    if(!data->ray->is_vert && data->ray->ray_down)
        data->color = get_color(data->texture[0], offset_x, offset_y);

    if(data->ray->is_vert && !data->ray->ray_right)
        data->color = get_color(data->texture[2], offset_x, offset_y);
        
    if(data->ray->is_vert && data->ray->ray_right)
        data->color = get_color(data->texture[3], offset_x, offset_y);
        
}
  

void    get_texture(t_game *data, int j)
{
    int     offset_x;
    int     offset_y;
    int     distance_from_top;

    if(data->ray->is_vert)
        offset_x = (int)data->ray->y_wall % TILE;
    else
        offset_x = (int)data->ray->x_wall % TILE;
    
    distance_from_top = j + (data->wall_projected_height / 2) - (S_HEIGHT / 2);
    offset_y = distance_from_top * ((double)TILE / data->wall_projected_height);

    if((offset_x >= 0 && offset_x < TILE) && (offset_y >= 0 && offset_y < TILE))
    {
        get_the_right_color(data, offset_x, offset_y);
    }
    
}

void    put_wall(t_game *data, int  wall_top, int wall_bottom, int i)
{
    int j;

    j =  wall_top;
    while(j < wall_bottom)
    {
        get_texture(data, j);
        my_mlx_pixel_put(data, i * WALL_WIDTH, j++, data->color);    
    }
}

void    put_ceiling(t_game *data, int walltop,int i)
{
    int j;
    double  distance;
    
    j = 0;
    while(j < walltop)
    {
        distance = (S_HEIGHT / 2 - j) / (double)(S_HEIGHT / 2);
        distance = 1 / (distance);
        my_mlx_pixel_put(data, i * WALL_WIDTH, j++, data->ceiling_color);
    }
}

void    put_floor(t_game *data, int wall_bottom, int i)
{
    int j;
    double  distance;

    j = wall_bottom;
    while(j < S_HEIGHT)
    {
        distance = (j - S_HEIGHT / 2) / (double)(S_HEIGHT / 2);
        distance = 1 / (distance);
        my_mlx_pixel_put(data, i * WALL_WIDTH, j++, data->floor_color);
    }
}
//)000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void    draw_rays(t_player *player, t_game *data)
{
    double i;
    // double x;
    // double y;
    // double j;
    
    i = 0;

    double rayAngle = player->rotationAngle - (FOV / 2);

    while(i < data->num_rays)//this while fill the array of rays while changing the rayAngle
    {//
            cast_rays(player, data, rayAngle);
            // j = 0;

            // draw_line(player, data, data->ray->x_hit, data->ray->y_hit);
            data->corrected_wall = data->ray->distance * cos(rayAngle - player->rotationAngle);
            data->distance_projectplan = (S_WIDTH / 2) / tan(FOV / 2);
            data->wall_projected_height = ((double)TILE / data->corrected_wall) * (double)data->distance_projectplan;
            
            int     WallTopPixel = (S_HEIGHT / 2) - (data->wall_projected_height / 2);
            if(WallTopPixel < 0)
                WallTopPixel = 0;
            int     WallBottomPixel = (S_HEIGHT / 2) + (data->wall_projected_height / 2);
            if(WallBottomPixel > S_HEIGHT)
                WallBottomPixel = S_HEIGHT;

            

            put_ceiling(data, WallTopPixel,i);
            put_wall(data,WallTopPixel, WallBottomPixel, i);
            put_floor(data, WallBottomPixel, i);
    //---------------------------------------------------------------------------------
        // int texture_x = (int)(rayAngle * data->tex_width / (2 * PI)) % data->tex_width;

        // // Draw the textured wall slice
        // for (int y = WallTopPixel; y < WallBottomPixel; y++)
        // {
        //     // Calculate the texture Y-coordinate based on the y-position of the wall slice
        //     double texture_pos = (y - (S_HEIGHT / 2 - wall_projected_height / 2)) * data->tex_height / wall_projected_height;
        //     if (texture_pos < 0) texture_pos = 0;
        //     if (texture_pos >= data->tex_height) texture_pos = data->tex_height - 1;

        //     // Sample the color from the texture (texture data is a 1D array of pixels)
        //     int color = get_texture_color(data->tex_data, data->tex_width, data->tex_height, texture_x, (int)texture_pos);

        //     // Draw the pixel at the correct position in the window using the color from the texture
        //     my_mlx_pixel_put(data, i * WALL_WIDTH, y, color);
        // }
    //---------------------------------------------------------------------------------

            // draw_rectangle(data, i * WALL_WIDTH, (S_HEIGHT / 2) - (data->wall_projected_height / 2) ,WALL_WIDTH, data->wall_projected_height);
        rayAngle += FOV / data->num_rays;
        i++;
    }

}


void    put_rays(t_game *data, t_player *player)
{
    double i;
    double x;
    double y;
    double j;
    
    i = 0;  
    double rayAngle = player->rotationAngle - (FOV / 2);

    while(i < data->num_rays)
    {
        j = 0;
            while(j < 20)
            {
                x = (player->x * MINIMAP) + cos(rayAngle) * j;
                y = (player->y * MINIMAP) + sin(rayAngle) * j;
    
                my_mlx_pixel_put(data, x, y, LIGHT_RED);
                /*WHERE WE WILL RENDER THE WALL AFTER*/

                j++;
            }
        rayAngle += FOV / data->num_rays;
        i++;    
    }
}