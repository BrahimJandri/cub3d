/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachid <rachid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:01:18 by rachid            #+#    #+#             */
/*   Updated: 2025/02/05 11:25:22 by rachid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Headers/cub3d.h"

void draw_circle(t_player *player, t_game *data) {
    int x, y;
    
    for (x = -player->radius; x <= player->radius; x++) 
    {
        for (y = -player->radius; y <= player->radius; y++)
        {
            // Check if the point (x, y) satisfies the circle equation
            if ((x * x + y * y) <= player->radius * player->radius)
            {
                my_mlx_pixel_put(data, (player->x + x) * MINIMAP, (player->y + y) * MINIMAP, RED);
            }
        }
    }
}

void    draw_line(t_player *player, t_game *data, double x_hit, double  y_hit )
{
    int x;
    int y;
    int i = 0;

    
    player->line_lenght = calcul_line_length(player->x, player->y, x_hit, y_hit);
    while(i < (int)player->line_lenght)
    {
        
        x = player->x + cos(player->rotationAngle) * i;
        y = player->y + sin(player->rotationAngle) * i;
        
        my_mlx_pixel_put(data->mlx, x, y, RED);            
        i++;
    }
    
    
}

void    draw_minimap(t_game *data)
{
	int	x;
	int	y;
	int color;
    
	y = 0;
	while (y < data->map_height)//is small than the height
	{
		x = 0;
		while (x < data->map_width)//is small than the width
		{
			color = check_number(data->map[y][x]);
			build_square(data, x * (TILE * MINIMAP) , y * (TILE * MINIMAP) ,color);
			x++;
		}
		y++;
	}
}

// void    build_square(t_game *data, int x, int y, int color)
// {   
//     for(int i = 0;i < TILE * MINIMAP; i++)
//     {
//         for(int j = 0; j < TILE * MINIMAP ; j++)
//         {
//             my_mlx_pixel_put(data, x + i, y + j, color);
//         }
//     }
    
// }

