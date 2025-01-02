/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachid <rachid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:27:31 by reddamss          #+#    #+#             */
/*   Updated: 2025/01/02 11:39:42 by rachid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int     player_control(int key, t_game *data)
{
    t_player *player;

    player = data->player;
    if (key == UP)
    {
        printf("up\n");
        player->walkDir = 1;// it adds 1 to walkdir to move forward
        update_player(data, data->player);// it will update the player forward only if the player
            // is in 0 (white space), once the player is in a wall cant update it anymore.
    }
    else if (key == DOWN)
    {
        printf("down\n");
        player->walkDir= -1;
        update_player(data, data->player);
    }
    else if (key == RIGHT)
    {
        player->turnDir = 0.02;
        // printf("right\n");
        update_rotation(data, data->player);
    }
    else if (key == LEFT)
    {
        player->turnDir = -0.02;    
        // printf("left\n");
        update_rotation(data, data->player);
    }
    else if(key == ESC)
    {
        exit(1);
    }
    return 1;
}


int     key_release(int key, t_game *data)
{
        t_player *player;

    player = data->player;
    if (key == UP)
    {
        // printf("up\n");
        player->walkDir = 0;// it adds 1 to walkdir to move forward
        update_player(data, data->player);// it will update the player forward only if the player
    }
    else if (key == DOWN)
    {
        // printf("down\n");
        player->walkDir= 0;
        update_player(data, data->player);
    }
    else if (key == RIGHT)
    {
        player->turnDir = 0;
        update_rotation(data, data->player);
    }
    else if (key == LEFT)
    {
        player->turnDir = 0;
        update_rotation(data, data->player);
    }
    else if(key == ESC)
    {
        exit(1);
    }
    return 1;
}

void    update_rotation(t_game *data, t_player *player)
{
    player->rotationAngle += player->turnDir * player->rotationSpeed;
        
    draw_map(data);    
}

void    update_player(t_game *data, t_player *player)
{
    double new_posx;
    double new_posy;
    
    new_posx = player->x + cos(player->rotationAngle) * player->walkDir * player->moveSpeed;
    new_posy = player->y + sin(player->rotationAngle) * player->walkDir * player->moveSpeed;
    
    
    printf("move game player position[%f][%f]\n", player->y, player->x);
    if(data->map[(int)new_posy / TILE][(int)new_posx / TILE] != '1')
    {
        printf("enterd\n");
        player->x = new_posx;
        player->y = new_posy;
    }
    draw_map(data);
}


    