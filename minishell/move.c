/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reddamss <reddamss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:27:31 by reddamss          #+#    #+#             */
/*   Updated: 2024/12/21 10:45:30 by reddamss         ###   ########.fr       */
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
        player->walkDir = 1;
        if(data->map[(int)player->y / TILE][(int)player->x / TILE] != '1')
            update_player(data, data->player);
        // player->walkDir = 0;
    }
    if (key == DOWN)
    {
        printf("down\n");
        player->walkDir= -1;
        if(data->map[(int)player->y / TILE][(int)player->x / TILE] != '1')
            update_player(data, data->player);
        // player-> = 0;
    }
    if (key == RIGHT)
    {
        player->turnDir = 0.1;
        printf("right\n");
        update_rotation(data, data->player);
        // player->turnDir = 0;
    }
    if (key == LEFT)
    {
        player->turnDir = -0.1;
        printf("left\n");
        update_rotation(data, data->player);
        // player->turnDir = 0;

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
   
    player->x += cos(player->rotationAngle) * player->walkDir * player->moveSpeed;
    player->y += sin(player->rotationAngle) * player->walkDir * player->moveSpeed;
    draw_map(data);
}

    