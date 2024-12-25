/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reddamss <reddamss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:27:31 by reddamss          #+#    #+#             */
/*   Updated: 2024/12/23 10:06:16 by reddamss         ###   ########.fr       */
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
    if (key == DOWN)
    {
        printf("down\n");
        player->walkDir= -1;
        update_player(data, data->player);
    }
    if (key == RIGHT)
    {
        player->turnDir = 0.1;
        printf("right\n");
        update_rotation(data, data->player);
    }
    if (key == LEFT)
    {
        player->turnDir = -0.1;
        printf("left\n");
        update_rotation(data, data->player);
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
    

    draw_map(data);
    
    if(data->map[(int)new_posy / TILE][(int)new_posx / TILE] != '1')
    {
        player->x = new_posx;
        player->y = new_posy;
    }
}


    