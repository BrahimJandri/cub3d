/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reddamss <reddamss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 11:12:27 by reddamss          #+#    #+#             */
/*   Updated: 2024/11/14 09:48:27 by reddamss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void    init_player(t_player *player)
{
    player->x = 90;
    player->y = 90;
    player->width = 1;
    player->height = 1;
    player->turn_direction = 0;
    player->walk_direction = 0;
    player->rotaion = PI / 2;
    return ;
}



void    my_move(int x, int y, t_game *data)
{
    int true;

    true = 0;
    if(data->map[(data->user->x + x) / 40][(data->user->y + y) / 40] != '1')
    {
        data->user->walk_direction += x + (cos(data->user->rotaion) * 10);
        data->user->turn_direction += y + (sin(data->user->rotaion) * 10);
        true = 1;
    }
    if(true)
    {
        printf("this is x= %d\nthis is y = %d\n", data->user->x, data->user->y);
        mlx_clear_window(data->mlx_ptr, data->win_ptr);
        draw_map(data);
        build_player(data, data->user->turn_direction ,data->user->walk_direction, RED);    
    }
}

int    move_player(int keycode, t_game *data)
{    
    if (keycode == UP || keycode == W)
        my_move(-1, 0, data);
	else if (keycode == DOWN || keycode == S)
        my_move(1, 0, data);
	else if (keycode == RIGHT || keycode == D)
        my_move(0, 1, data);
	else if (keycode == LEFT || keycode == A)
        my_move(0, -1, data);
	return (0);
}

void    draw_line(void  *mlx, void *win, int x_start, int y, int len)
{
    for(int x = x_start; x < x_start + len; x++)
        mlx_pixel_put(mlx, win, x, y, RED);
}

void    create_player(t_game *data)
{
    t_player *player;

    player = malloc(sizeof(t_player));

    init_player(player);
    
    data->user = player;
    
    // draw_line(data->mlx_ptr, data->win_ptr,player.x, player.y,30);  
    
}