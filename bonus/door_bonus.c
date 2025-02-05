/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachid <rachid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 09:41:23 by rachid            #+#    #+#             */
/*   Updated: 2025/02/05 09:49:26 by rachid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Headers/cub3d_bonus.h"

void    init_door(t_game *data)
{
    int index;
    int i;
    int j;
    
    i = 0;
    index = 0;
    while(i < data->map_height)
    {
        j = 0;
        while(j < data->map_width)
        {
            if(data->map[i][j] == 'D')
            {
                assign_index(data, index, i, j);
                index++;
            }
            j++;
        }
        i++;
    }
}

void    alloc_doors(t_game * data)
{
    t_door *door;
    //getting the number of the doors
    data->door_num = get_doors_num(data); 
    if(data->door_num)
    {
        door = malloc(sizeof(t_door) * data->door_num);
        if(!door)
        {
            //error message 
            exit(16);
        }
    }
    data->door = door;
}

int    get_doors_num(t_game *data)
{
    int door;
    int i;
    int j;

    i = 0;
    door = 0;
    while(i < data->map_height)
    {
        j = 0;
        while(j < data->map_width)
        {
            if(data->map[i][j] == 'D')
                door++;
            j++;
        }
        i++;
    }
    return (door);
}

void    assign_index(t_game *data, int index, int y, int x)
{
    data->door[index].x = x;
    data->door[index].y = y;
    data->door[index].open = false;
}    

void    ft_player_wall_hit(t_game *data)
{
    int x;
    int y;
    int index;

    cast_rays(data->player, data, data->player->rotationAngle);
    x = (int)(data->ray->x_wall / TILE);
    y = (int)(data->ray->y_wall / TILE);
    // printf("distance = %f\n", data->ray->distance);
    if(x >= 0 && x < data->map_width && y >= 0 && y < data->map_height)
    {
        if(data->map[y][x] == 'D' && data->ray->distance < DOOR_DISTANCE)
        {
            // printf("YAAAAAAAAAAAAAAAY\n");
            index = get_index(data, y, x);
            if(index != -1)
                data->door[index].open = !data->door[index].open;
        }
    }
}