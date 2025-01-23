/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachid <rachid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:04:23 by reddamss          #+#    #+#             */
/*   Updated: 2025/01/22 10:41:21 by rachid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./Headers/cub3d.h"


void	draw_map(t_game *data)
{
    data->img->img = mlx_new_image(data->mlx, S_WIDTH, S_HEIGHT);  
    if(!data->img)
        return ;
    data->img->addrs = mlx_get_data_addr(data->img->img, &data->img->bpp, &data->img->size_line, &data->img->endian);

    // draw_minimap(data);
    // draw_line(data->player, data);
    // line(data->player, data);
    // draw_circle(data->player, data);
    
    draw_rays(data->player, data);
    
    mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0,0);
    mlx_destroy_image(data->mlx, data->img->img);
    // render_walls(data, data->player);
    // cast_rays(data->player, data, data->player->rotationAngle);
    
}


void ft_write_floor(t_game *data, int i, int color)
{
    int j;
    double distance;
    int shaded_color;

    // Start from the bottom of the screen and go downwards
    j = data->num_rays; // Assuming `num_rays` represents the start line of the floor (adjust accordingly)
    while (j < S_HEIGHT)
    {
        // Calculate the distance based on the vertical screen position (j)
        distance = (j - S_HEIGHT / 2) / (double)(S_HEIGHT / 2);
        distance = 1 / distance;  // Perspective effect: farther = smaller and darker
        
        // Apply shading to the color based on the distance
        shaded_color = shade_walls(color, distance);

        // Draw the pixel on the floor
        my_mlx_pixel_put(data, i, j, shaded_color);
        j++; // Move downwards to the next row
    }
}

void ft_write_ceiling(t_game *data, int i, int color)
{
    int j;
    double distance;
    int shaded_color;

    // Start from the top of the screen and go upwards until the start of the walls
    j = 0;  // Start from the very top of the screen
    while (j < data->num_rays)  // Draw only above the wall start line
    {
        // Calculate the distance based on the vertical screen position (j)
        distance = (S_HEIGHT / 2 - j) / (double)(S_HEIGHT / 2);
        distance = 1 / distance;  // Perspective effect: farther = smaller and darker
        
        // Apply shading to the color based on the distance
        shaded_color = shade_walls(color, distance);

        // Draw the pixel on the ceiling
        my_mlx_pixel_put(data, i, j, shaded_color);
        j++; // Move upwards to the next row
    }
}




void draw_map(t_game *data)
{
    int i;
    int floor_color = data->floor_color;  // Use the floor color from the config
    int ceiling_color = data->ceiling_color;  // Use the ceiling color from the config

    // Create a new image to render to
    data->img = mlx_new_image(data->mlx, S_WIDTH, S_HEIGHT);
    if (!data->img)
        return;
    data->addrs = mlx_get_data_addr(data->img, &data->bpp, &data->size_line, &data->endian);

    // Draw the 2D grid of the map (optional based on your use case)
    // For example, you can render walls and objects here.
    // This will depend on the game logic and how the world map is structured.
    int x = 0;
    int y = 0;
    while (y < data->map_height)
    {
        x = 0;
        while (x < data->map_width)
        {
            int color = check_number(data->map[y][x]);  // Assume this gives a color based on the tile type
            build_square(data, x * TILE, y * TILE, color);
            x++;
        }
        y++;
    }

    // Draw floor and ceiling for each vertical column of the screen
    for (i = 0; i < S_WIDTH; i++)
    {
        // Render floor and ceiling with their respective colors
        ft_write_floor(data, i, floor_color);  // Render floor
        ft_write_ceiling(data, i, ceiling_color);  // Render ceiling
    }

    // Optionally, draw other elements like player, rays, etc.
    // draw_circle(data->player, data);
    draw_rays(data->player, data);

    // Display the final image in the window
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    mlx_destroy_image(data->mlx, data->img);
}



// void	draw_map(t_game *data)
// {
// 	int	x;
// 	int	y;
// 	int color;

//     data->img = mlx_new_image(data->mlx, S_WIDTH, S_HEIGHT);  
//     if(!data->img)
//         return ;
//     data->addrs = mlx_get_data_addr(data->img, &data->bpp, &data->size_line, &data->endian);
//     // printf("bpp = %d, size = %d, endian = %d\n", data->bpp, data->size_line, data->endian);
//     // exit(1);
// 	y = 0;
// 	while (y < data->map_height)//is small than the height
// 	{
// 		x = 0;
// 		while (x < data->map_width)//is small than the width
// 		{
// 			color = check_number(data->map[y][x]);
// 			build_square(data, x * TILE, y * TILE ,color);
//             // sleep(1);
// 			x++;
// 		}
// 		y++;
// 	}
//     // printf("map->height = %d, map_width = %d\n",data->map_height, data->map_width);
//     // printf("playerx = %f player y = %f\n", data->player->x , data->player->y);
//     // exit(1);

//     // sleep(100);
    
    
//     // draw_line(data->player, data);
//     // line(data->player, data);
//     draw_circle(data->player, data);
    
//     draw_rays(data->player, data);
    
//     mlx_put_image_to_window(data->mlx, data->win, data->img, 0,0);
//     mlx_destroy_image(data->mlx, data->img);
//     // sleep(5);
//     // exit(1);
//     // render_walls(data, data->player);
//     // cast_rays(data->player, data, data->player->rotationAngle);
    
// }



int get_texture_color(unsigned int *texture_data, int tex_width, int tex_height, int x, int y)
{
    // Make sure the x and y are within bounds
    if (x < 0 || x >= tex_width || y < 0 || y >= tex_height) {
        return 0; // Return black if out of bounds (or any other default color)
    }

    // Get the pixel color as an unsigned int (RGBA format) 
    return texture_data[y * tex_width + x];
}

//)000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

int    get_color(t_game *data, int x, int y)
{
    int color;

    color = *(int *)(data->texture->tex_data + (y * data->texture->size_line) + x
		* (data->texture->bpp / 8));
    
    return color;
}



void    get_the_right_color(t_game *data, int offset_x, int offset_y)
{
    data->color = get_color(data, offset_x, offset_y);
}


void    get_texture(t_game *data, int j)
{
    int     offset_x;
    int     offset_y;
    int     distance_from_top;

    if(data->ray->is_vert)
        offset_x = (int)data->ray->y_wall % TEX;
    else
        offset_x = (int)data->ray->x_wall % TEX;
    
    distance_from_top = j + (data->wall_projected_height / 2) - (S_HEIGHT / 2);
    offset_y = distance_from_top * (TEX / data->wall_projected_height);

    if((offset_x >= 0 && offset_x < TEX - 1) && (offset_y >= 0 && offset_y < TEX - 1))
    {
        get_the_right_color(data, offset_x, offset_y);
    }
    
}

void    put_wall(t_game *data, int  wall_top, int wall_bottom,int i)
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
    int shaded;
    
    j = 0;
    while(j < walltop)
    {
        distance = (S_HEIGHT / 2 - j) / (double)(S_HEIGHT / 2);
        distance = 1 / (distance);
        shaded = shade_walls(BLUE_SKY, distance);
        my_mlx_pixel_put(data, i * WALL_WIDTH, j++, shaded);
    }
}

void    put_floor(t_game *data, int wall_bottom, int i)
{
    int j;
    double  distance;
    int shaded;

    j = wall_bottom;
    while(j < S_HEIGHT)
    {
        distance = (j - S_HEIGHT / 2) / (double)(S_HEIGHT / 2);
        distance = 1 / (distance);
        shaded = shade_walls(EARTH_COLOR, distance);
        my_mlx_pixel_put(data, i * WALL_WIDTH, j++, shaded);
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
            data->wall_projected_height = (TILE / data->corrected_wall) * data->distance_projectplan;
            
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

            // draw_rectangle(data, i * WALL_WIDTH, (S_HEIGHT / 2) - (wall_projected_height / 2) ,WALL_WIDTH, wall_projected_height);
            
            // while(j < data->ray->distance)
            // {
            //     x = player->x + cos(rayAngle) * j;
            //     y = player->y + sin(rayAngle) * j;
    
            //     my_mlx_pixel_put(data, x, y, RED);
            //     /*WHERE WE WILL RENDER THE WALL AFTER*/

            //     j++;
            // }
            // reset_window(data,0, 0);
            // mlx_destroy_image(data->mlx);
            // draw_line(player, data, x, y);
        rayAngle += FOV / data->num_rays;
        i++;
    }

}
