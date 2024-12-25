/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reddamss <reddamss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:04:23 by reddamss          #+#    #+#             */
/*   Updated: 2024/12/25 11:20:51 by reddamss         ###   ########.fr       */
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
        printf("%2.f\n", player->rotationAngle);
        x = player->x + cos(player->rotationAngle) * i;
        y = player->y + sin(player->rotationAngle) * i;
        printf("x= %d\ny= %d\n", x, y);
        
        mlx_pixel_put(data->mlx, data->win, x, y, RED);
        i++;
    }
    
}



void	draw_map(t_game *data)
{
	int	x;
	int	y;
	int color;

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


void    draw_rays(t_player *player, t_game *data)
{
    double i;
    double x;
    double y;
    double j;
    
    i = 0;

    double rayAngle = player->rotationAngle - (FOV / 2);
    
    while(i < data->num_rays)//this while fill the array of rays while changing the rayAngle
    {//
        // printf("rayAngle is %.2lf.\n", rayAngle);

        /*_______________________________________________*/
            j = 0;
            while(j < player->line_lenght)
            {
                x = player->x + cos(rayAngle) * j;
                y = player->y + sin(rayAngle) * j;
    
                mlx_pixel_put(data->mlx, data->win, x, y, RED);
                j++;
            }
        /*_______________________________________________*/
        
        // rays[(int)i] = rayAngle;
        rayAngle += FOV / data->num_rays;
        i++;
    }
}

//NORMALIZE THE VALUE OF THE ANGLE