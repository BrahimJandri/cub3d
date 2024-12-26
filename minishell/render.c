/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reddamss <reddamss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:04:23 by reddamss          #+#    #+#             */
/*   Updated: 2024/12/26 18:17:12 by reddamss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void    draw_line(t_player *player, t_game *data)
{
    int x;
    int y;
    int i = 0;
    
    while(i < player->line_lenght)
    {
        // printf("%2.f\n", player->rotationAngle);
        x = player->x + cos(player->rotationAngle) * i;
        y = player->y + sin(player->rotationAngle) * i;
        // printf("x= %d\ny= %d\n", x, y);
        
        mlx_pixel_put(data->mlx, data->win, x, y, RED);
        i++;
    }
    
}



void	draw_map(t_game *data)
{
	int	x;
	int	y;
	int color;
    // double ray_angle;

	y = 0;
	while (y < data->map_y)//is small than the height
	{
		x = 0;
		while (x < data->map_x - 1)//is small than the width
		{
			color = check_number(data->map[y][x]);
			build_square(data, x * TILE, y * TILE ,color);
			x++;
		}
		y++;
	}
    
    draw_circle(data->player, data);
    draw_line(data->player, data);
    draw_rays(data->player, data);
    // cast_rays(data->player, data);

    // ray_angle = normalize_angle();
    
}



void    build_square(t_game *data, int x, int y, int color)
{

    for(int i = 0;i < TILE; i++)
    {
        for(int j = 0; j < TILE; j++)
        {
            mlx_pixel_put(data->mlx, data->win, x + i, y + j, color);
            // usleep(10);
        }
    }
}


int    check_number(char c)
{
    if(c == '1')
        return GREY;
    if(c == '0' || c == 'P')
        return WHITE;
    return GOLDEN;
}

void    cast_rays(t_player *player, t_game *data, double angle)
{
    t_ray *ray = data->ray;
    // bool    h_wall_hit;
    angle = normalize_angle(angle);


    
    ray->ray_down = angle > 0 && angle < PI;
    ray->ray_up = !ray->ray_down;


    ray->ray_right = angle < (PI * 0.5) || angle > PI * 1.5; //HERE
    ray->ray_left = !ray->ray_left;
    
    printf("right = %d\n", ray->ray_right);

    ray->y_intercept = floor(TILE/ player->y) * TILE;
    if(ray->ray_down)
        ray->y_intercept += TILE;
    
    ray->x_intercept = player->x + (ray->y_intercept - player->y) / tan(angle);
    //calculating the xstep and ystep
    ray->y_steps = TILE;
    if(ray->ray_up)
        ray->y_steps *= -1;
        
        
    ray->x_steps = TILE / tan(angle);
    if(ray->ray_left && ray->x_steps > 0)
        ray->x_steps *= -1;
    if(ray->ray_right && ray->x_steps < 0)
        ray->x_steps *= -1;
    //__________________________________________________
    // h_wall_hit = false;
    
    //__________________________________________________
}





double      normalize_angle(double angle)
{
    angle =  fmod(PI * 2, angle);
    if(angle < 0)
    {
        angle = angle + (PI * 2);
    }
    return angle;
}  




/*__DRAWING_RAYS_WITH_FIXED_LENGTH__*/
void    draw_rays(t_player *player, t_game *data)
{
    double i;
    // double x;
    // double y;
    // double j;
    
    i = 0;

    double rayAngle = player->rotationAngle - (FOV / 2);
    
    cast_rays(player,data,rayAngle);
    while(i < data->num_rays)//this while fill the array of rays while changing the rayAngle
    {//
        // printf("rayAngle is %.2lf.\n", rayAngle);

        /*_______________________________________________*/
            // j = 0;
            /////////////////////////////////////////////////////////////////
            ///////////      CASTING EACH RAY TO HIT WALL BELLOW     ////////
            ////////////////////////////////////////////////////////////////
            // while(j < player->line_lenght)
            // {
            //     x = player->x + cos(rayAngle) * j;
            //     y = player->y + sin(rayAngle) * j;
    
            //     mlx_pixel_put(data->mlx, data->win, x, y, RED);
            //     j++;
            // }
        /*_______________________________________________*/
        
        // rays[(int)i] = rayAngle;
        rayAngle += FOV / data->num_rays;
        i++;
    }
}

//NORMALIZE THE VALUE OF THE ANGLE
