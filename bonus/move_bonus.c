/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachid <rachid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:27:31 by reddamss          #+#    #+#             */
/*   Updated: 2025/01/27 18:26:36 by rachid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./Headers/cub3d_bonus.h"


void    destroy_xpm(t_game *data)
{
    int i;

    i = 0;
    while(i < 4)
    {
        mlx_destroy_image(data->mlx, data->texture[i]->img);
        i++;
    }
    i = 0;
    while(i < 4)
        free(data->texture[i++]);
    return ;
}

int     player_control(int key, t_game *data)
{
    t_player *player;

    player = data->player;
    if (key == UP || key == W)
        player->walkDir = 1;
    else if (key == DOWN || key == S)
        player->walkDir= -1;
    else if (key == RIGHT)
        player->turnDir = 0.02;
    else if (key == LEFT)
        player->turnDir = -0.02;
    else if (key == A)
        player->sideDir = -1;
    else if(key == D)
        player->sideDir = 1;
    else if(key == ESC)
    { 
        free(data->ray);
        destroy_xpm(data);
        mlx_destroy_window(data->mlx, data->win);
        mlx_destroy_display(data->mlx);
        free(data->mlx);
        free(data->player);
        free(data->img);
        free_all(data);
        exit(1);
    }
    return 1;
}


int     key_release(int key, t_game *data)
{
        t_player *player;

    player = data->player;
    if (key == UP || key == W)
        player->walkDir = 0;
    else if (key == DOWN || key == S)
        player->walkDir = 0;
    else if (key == RIGHT)
        player->turnDir = 0;
    else if (key == LEFT)
        player->turnDir = 0;

    else if (key == A)
        player->sideDir = 0;
    else if(key == D)
        player->sideDir = 0;
    return 1;
}

void    update_sides(t_game *data, t_player *player)
{
    double  new_posx;
    double  new_posy;
    int x;
    int y;
    
    new_posx = player->x + cos(player->rotationAngle + (PI / 2)) * player->sideDir * player->moveSpeed;
    new_posy = player->y + sin(player->rotationAngle + (PI / 2)) * player->sideDir * player->moveSpeed;
    
    x = (int)player->x / TILE;
    y = (int)player->y / TILE;
    
    if(data->map[y][(int)new_posx / TILE] != '1')
        player->x = new_posx;
    if(data->map[(int)new_posy / TILE][x] != '1')
        player->y = new_posy;
}

void    update_player(t_game *data, t_player *player)
{
    int x;
    int y;
    double new_posx;
    double new_posy;
    
    new_posx = player->x + cos(player->rotationAngle) * player->walkDir * player->moveSpeed;
    new_posy = player->y + sin(player->rotationAngle) * player->walkDir * player->moveSpeed;

    x = (int)player->x / TILE;
    y = (int)player->y / TILE;
    
    if(data->map[y][(int)new_posx / TILE] != '1')
        player->x = new_posx;
    if(data->map[(int)new_posy / TILE][x] != '1')
        player->y = new_posy;
}


    