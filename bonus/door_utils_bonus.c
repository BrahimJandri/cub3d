/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachid <rachid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 09:44:07 by rachid            #+#    #+#             */
/*   Updated: 2025/02/05 10:55:13 by rachid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Headers/cub3d_bonus.h"

int     get_index(t_game *data, int y, int x)
{
    int index;

    index = 0;
    while(index < data->door_num)
    {
        printf("data->door[%d].x = %d, data->door[%d].y = %d\n", index, data->door[index].x, index, data->door[index].y);
        if(data->door[index].x == x && data->door[index].y == y)
            return index;
        index++;
    }
    printf("_________________________________________________\n");
    return (-1);
}

// will find it in render file, get_data function
int     x_accessibility(t_game *data, int y, double new_x)
{
    int index;

    // printf("y == %d, x = %d\n", y, (int)(new_x / TILE));
    index = get_index(data, y, (new_x / TILE));
    if(index == -1)
        exit(1);
    printf("accessible %d\n", data->door[index].open);
    if(data->door[index].open)
        return 1;
    else
        return 0;
}

// will find it in render file, get_data function
int     y_accessibility(t_game *data, int x, double new_y)
{
    int index;

    //gets the index of the tile
    index = get_index(data, new_y / TILE, x);
    if(index == -1)
        exit(13);
    if(data->door[index].open)
        return 1;
    else
        return 0;
}

int    y_side_accessibility(t_game *data, double y, double x)
{
    int index;
    
    (void)x;

    printf("(14) y == %d, x = %d\n", (int)(y / TILE), (int)(data->player->x / TILE));
    index = get_index(data, (int)(y / TILE), (int)(data->player->x / TILE));
    
    if(index == -1)
        return 0;
    if(data->door[index].open)
        return 1;
    else
        return 0;
}

int    x_side_accessibility(t_game *data, double y, double x)
{
    int index;
    
    printf("(15) y == %d, x = %d\n", (int)(y / TILE), (int)(x / TILE));
    index = get_index(data, floor(y / TILE), floor(x / TILE));
    if(index == -1)
        return 0;   
    if(data->door[index].open)
        return 1;
    else
        return 0;
}