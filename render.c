/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reddamss <reddamss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:04:23 by reddamss          #+#    #+#             */
/*   Updated: 2025/01/15 11:33:16 by reddamss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./Headers/cub3d.h"


double      calcul_line_length(double   x1, double y1, double x2, double y2)
{
    return(sqrt(pow(x1 - x2,2) + pow(y1 - y2, 2)));
}

// void    line(t_player *player, t_game *data)
// {
//     int i;
//     double x;
//     double y;

//     i = 0;
    
//     while(i < (int)player->line_lenght)
//     {
        
//         // printf("%2.f\n", player->rotationAngle);
//         x = player->x + cos(player->rotationAngle) * i;
//         y = player->y + sin(player->rotationAngle) * i;
//         // printf("x= %d\ny= %d\n", x, y);
        
//         mlx_pixel_put(data->mlx, data->win, x, y, RED);
//         // printf("x = %d y = %d\n",x,y);
            
//         // sleep(5);
//         i++;
//     }
// }




void    draw_line(t_player *player, t_game *data, double x_hit, double  y_hit )
{
    int x;
    int y;
    int i = 0;

    
    player->line_lenght = calcul_line_length(player->x, player->y, x_hit, y_hit);
    // printf("xhit = %f, yhit = %f\n", x_hit, y_hit);
    while(i < (int)player->line_lenght)
    {
        
        // printf("%2.f\n", player->rotationAngle);
        x = player->x + cos(player->rotationAngle) * i;
        y = player->y + sin(player->rotationAngle) * i;
        // printf("x= %d\ny= %d\n", x, y);
        
        my_mlx_pixel_put(data->mlx, x, y, RED);
        // printf("x = %d y = %d\n",x,y);
            
        // sleep(5);
        i++;
    }
    
    
}

int shade_walls(int color, double distance)
{
    int r, g, b;
    int shaded_color;

    // Ensure distance is not zero to avoid division by zero errors
    if (distance < 0.1)
        distance = 0.1;

    // Extract RGB components from the color
    r = (color >> 16) & 0xFF; // Extract the red component
    g = (color >> 8) & 0xFF;  // Extract the green component
    b = color & 0xFF;         // Extract the blue component

    // Apply shading based on the distance (the farther away, the darker the color)
    r = (int)(r / distance);
    g = (int)(g / distance);
    b = (int)(b / distance);

    // Ensure the RGB values are within the valid range [0, 255]
    if (r > 255) r = 255;
    if (g > 255) g = 255;
    if (b > 255) b = 255;
    if (r < 0) r = 0;
    if (g < 0) g = 0;
    if (b < 0) b = 0;

    // Combine the RGB components back into a single color value
    shaded_color = (r << 16) | (g << 8) | b;

    return shaded_color;
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
    draw_circle(data->player, data);
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



void    build_square(t_game *data, int x, int y, int color)
{
    // if (!data || !data->addrs) {
    //     fprintf(stderr, "Error: data or data->addrs is NULL\n");
    //     exit(22);
    // }    
    // if (x < 0 || x >= S_WIDTH || y < 0 || y >= S_HEIGHT) {
    //     fprintf(stderr, "Error: x or y is out of bounds\n");
    //     exit(22);
    // }

    // int b = 0;
    
    for(int i = 0;i < TILE -1; i++)
    {
        for(int j = 0; j < TILE -1; j++)
        {
            // printf("inside\n");
            my_mlx_pixel_put(data, x + i, y + j, color);
            // mlx_pixel_put(data->mlx, data->win, x + i, y + j, color);
            // usleep(100);
            // printf("hello %d\n", b++);
        }
    }
    // exit(1);    
    // sleep(2);
    
}


int    check_number(char c)
{
    if(c == '1')
        return GREY;
    if(c == '0' || c == 'N')
        return WHITE;
    return GOLDEN;
}



int    is_it_wall(t_game *data, double   x, double   y)
{
    if((x < 0 || x > data->map_width * TILE) || (y < 0 || y > data->map_height * TILE))
    {
        // printf("Happend and x = %2.f, y = %2.f\n", x, y);
        return 1;
    }
    double map_x;
    double map_y;

    map_x = floor(x / TILE);
    map_y = floor(y / TILE);
    // printf("mapx = %2.lf. mapy = %2.lf\n",map_x, map_y);
    return(data->map[(int)map_y ][(int)map_x] != '0');
}


void    cast_rays(t_player *player, t_game *data, double angle)
{

    (void)player;
    bool    found_wall;
    double  hit_wallx;
    double  hit_wally;
    

    (void)hit_wallx;
    (void)hit_wally;
    (void)found_wall;
    found_wall = false;
    t_ray *ray = data->ray;
    // bool    h_wall_hit;
    angle = normalize_angle(angle);


    
    ray->ray_down = angle > 0 && angle < PI;
    ray->ray_up = !ray->ray_down;
    

    ray->ray_right = angle < (PI * 0.5) || angle > (1.5 * PI); //HERE
    ray->ray_left = !ray->ray_right;
    
    // printf("down = %d, with angle: %2.3lf\n", ray->ray_down, angle);
    // printf("the player->y = %lf\n",player->y);
    ray->y_intercept = floor(player->y / TILE) * TILE;
    if(ray->ray_down)
        ray->y_intercept += TILE;
    
    // printf("the player->x = %lf\n",player->x);
    ray->x_intercept = player->x + (ray->y_intercept - player->y) / tan(angle);
    //calculating the xstep and ystep
    ray->y_steps = TILE;
    if(ray->ray_up)
        ray->y_steps *= -1;
        
    // printf("intecept_x = %lf, intercept_y = %lf\n",ray->x_intercept, ray->y_intercept);

    ray->x_steps = TILE / tan(angle);
    if(ray->ray_left && ray->x_steps > 0)
        ray->x_steps *= -1;
    if(ray->ray_right && ray->x_steps < 0)
        ray->x_steps *= -1;


    double  next_xtouch;
    double  next_ytouch;

    next_xtouch = ray->x_intercept;
    next_ytouch = ray->y_intercept;

            /*  DID NOT UNDERSTAND YET THIS  */ 
    if (ray->ray_up)
        next_ytouch--;
        
    // printf("touch_x = %lf, touch_y = %lf\n",next_xtouch, next_ytouch);//x = 220, y =120

    while(next_ytouch > 0 && next_ytouch < S_HEIGHT && next_xtouch > 0 && next_xtouch < S_WIDTH)
    {
        // printf("H checking\n");
        if(is_it_wall(data, next_xtouch, next_ytouch))
        {
            // printf("touched it\n");
            found_wall = true;
            // printf("H found Wall\n");
            hit_wally = next_ytouch;
            hit_wallx = next_xtouch;
            break ;
        }
        else
        {
            next_xtouch += ray->x_steps;
            next_ytouch += ray->y_steps;
        }
    }


          ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////VERTICAL GRID INTERSECTION/////////////////////////////////////////////////
       ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////




    bool    found_vert_wall;
    double  vert_hit_wallx;
    double  vert_hit_wally;
    

    (void)vert_hit_wallx;
    (void)vert_hit_wally;
    (void)found_vert_wall;
    found_vert_wall = false;
    

    
    // printf("down = %d, with angle: %2.3lf\n", ray->ray_down, angle);
    
    // printf("the player->x = %lf player-> y = %lf\n",player->x, player->y);//x = 220, y= 100;
    ray->x_intercept = floor(player->x / TILE) * TILE;
    if(ray->ray_right)
        ray->x_intercept += TILE;
    
    //at the beginning the y_intercept is negative
    ray->y_intercept = player->y + ((ray->x_intercept - player->x) * tan(angle));
    
    //calculating the xstep and ystep

    // printf("intecept_x = %lf, intercept_y = %lf\n",ray->x_intercept, ray->y_intercept);
    ray->x_steps = TILE;
    if(ray->ray_left)
        ray->x_steps *= -1;
        
        
    ray->y_steps = TILE * tan(angle);
    // printf("y_steps = %lf\n", ray->y_steps);
    if(ray->ray_up && ray->y_steps > 0)
        ray->y_steps *= -1;
    if(ray->ray_down && ray->y_steps < 0)
        ray->y_steps *= -1;



    double  vert_next_xtouch;
    double  vert_next_ytouch;

    vert_next_xtouch = ray->x_intercept;
    vert_next_ytouch = ray->y_intercept;

            /*  DID NOT UNDERSTAND YET THIS  */ 
    if (ray->ray_left)
        vert_next_xtouch--;

    vert_hit_wallx = 1;
    vert_hit_wally = 1;
    while(vert_next_ytouch >= 0 && vert_next_ytouch <= S_HEIGHT && vert_next_xtouch >= 0 && vert_next_xtouch <= S_WIDTH)
    {
        if(is_it_wall(data, vert_next_xtouch, vert_next_ytouch))
        {
            // printf("VER touched it\n");
            found_vert_wall = true;
            // printf("V found Wall\n");
            vert_hit_wally = vert_next_ytouch;
            vert_hit_wallx = vert_next_xtouch;
            break ;
        }
        else
        {
            vert_next_xtouch += ray->x_steps;
            vert_next_ytouch += ray->y_steps;
        }
    }
    // printf("hit_x = %lf, hit_y = %lf\n", vert_hit_wallx, vert_hit_wally);
    // draw_line(player, data, vert_hit_wallx, vert_hit_wally);

////////smon ghan tzrt manwa i9rbn i lplayer
    double  ver_hits_distance;
    double  horz_hits_distance;


    
    if(found_vert_wall)
        ver_hits_distance = calcul_line_length(player->x, player->y, vert_hit_wallx, vert_hit_wally);
    else
        ver_hits_distance = 9199999999999999999;
    if(found_wall)
        horz_hits_distance = calcul_line_length(player->x, player->y, hit_wallx, hit_wally);
    else
        horz_hits_distance = 9199999999999999999;

    // printf("H_distance = %2.f V_distance = %2.f\n", horz_hits_distance, ver_hits_distance);
    if(horz_hits_distance < ver_hits_distance)
    {
        ray->x_hit = hit_wallx;
        ray->y_hit = hit_wally;
        ray->distance = horz_hits_distance;
    // printf("here is horz\n");
        
    }
    else
    {
        ray->x_hit = vert_hit_wallx;
        ray->y_hit = vert_hit_wally;
        ray->distance = ver_hits_distance;
    // printf("here is vertical \n");

    }

    // printf("distance = %2.f\n",ray->distance);
    // player->rotationAngle = angle;
    
    // cast_rays(player, data, rayAngle);
        
        // draw_line(player, data, data->ray->x_hit, data->ray->y_hit);
    

    
    // draw_line(player, data, ray->x_hit, ray->y_hit);
    // draw_line(player, data, hit_wallx, hit_wally);
    //__________________________________________________
    // h_wall_hit = false;
    
    //__________________________________________________
}


// void    clearColorbuffer(t_game *data, unsigned int color)
// {
//     for(int x = 0; x < S_WIDTH; x++)
//     {
//         for(int y = 0; y < S_HEIGHT; y++)
//         {
//             data->colorbuffer[(S_WIDTH * y) + x] = color;
//         }
//     }
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


double      normalize_angle(double angle)
{
    angle = fmod(angle, TWO_PI);
    if(angle < 0)
    {
        angle = angle + TWO_PI;
    }
    return angle;
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
            // sleep(1);
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
            
            // printf("distance = %2.f\n", data->ray->distance);
            while(j < data->ray->distance)
            {
                x = player->x + cos(rayAngle) * j;
                y = player->y + sin(rayAngle) * j;
    
                // printf("x = %2.f, y = %2.f\n", x, y);
                my_mlx_pixel_put(data, x, y, RED);
                /*WHERE WE WILL RENDER THE WALL AFTER*/
                // exit(1);

                j++;
            }
            // reset_window(data,0, 0);
            // mlx_destroy_image(data->mlx);
            // draw_line(player, data, x, y);
        rayAngle += FOV / data->num_rays;
        i++;
    }

    // printf("player positions are[%f][%f]\n", player->y, player->x);
}


// void    reset_window(t_game *data, int x, int y)
// {
//     data->img = mlx_new_image(data->mlx, S_WIDTH, S_HEIGHT);
//     data->addrs = mlx_get_data_addr(data->img, data->bitppixel,data->size_line, data->endian);
//     mlx_put_image_to_window(data->mlx, data->win, data-> img, x, y)
    
// }

/*__DRAWING_RAYS_WITH_FIXED_LENGTH__*/
// void    draw_rays(t_player *player, t_game *data)
// {
//     double i;
//     // double x;
//     // double y;
//     // double j;
    
//     i = 0;

//     double rayAngle = player->rotationAngle - (FOV / 2);
    
//     while(i < data->num_rays)//this while fill the array of rays while changing the rayAngle
//     {//
//         // printf("rayAngle is %.2lf.\n", rayAngle);
//         cast_rays(player,data,rayAngle);


//         rayAngle += FOV / data->num_rays;
//         i++;
//     }
// }

//NORMALIZE THE VALUE OF THE ANGLE
