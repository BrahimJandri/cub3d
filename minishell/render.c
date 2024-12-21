/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reddamss <reddamss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:04:23 by reddamss          #+#    #+#             */
/*   Updated: 2024/12/18 16:01:02 by reddamss         ###   ########.fr       */
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
    return BLACK;
}