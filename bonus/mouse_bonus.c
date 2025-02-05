/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachid <rachid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 09:52:42 by rachid            #+#    #+#             */
/*   Updated: 2025/02/05 09:53:19 by rachid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Headers/cub3d_bonus.h"

//1 = right, 3 = left
int     click_press(int key, int x, int y, t_game *data)
{
    t_player *player;
    // mini_map(data);
    // draw_circle(data->player, data);
    player = data->player;
    (void)x;
    (void)y;
    if(key == 1)
    {
        player->turnDir = -0.02;
    }
    else if(key == 3)
    {
        player->turnDir = 0.02;
    }
    return 0;
}

int     click_release(int key, int x, int y, t_game *data)
{
    t_player *player;

    player = data->player;
    (void)x;
    (void)y;
    if(key == 1)
    {
        player->turnDir = 0;
    }    // mini_map(data);
    // draw_circle(data->player, data);
    else if(key == 3)
    {
        player->turnDir = 0;
    }
    return 0;
}
