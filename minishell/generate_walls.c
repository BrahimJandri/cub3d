/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_walls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachid <rachid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:50:53 by rachid            #+#    #+#             */
/*   Updated: 2025/01/04 11:05:26 by rachid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void    render_walls(t_game *data, t_player *player)
// {
//     int i;
//     double wall_projected_height;
//     double distance_projectplan;
//     i = 0;

//     while(i < data->num_rays)
//     {
//         // cast_rays(player,)

//         wall_projected_height = TILE / data->ray->distance * distance_projectplan;

//         distance_projectplan = (S_WIDTH / 2) / tan(FOV / 2);
//         draw_rectangle(data, (S_WIDTH / 2) - wall_projected_height ,WALL_WIDTH, wall_projected_height)


        
//     }
// }

void    draw_rectangle(t_game *data, int x, int y, int width, int height)
{
    int i;
    int j;


    i = 0;
    printf("x = %d, y = %d, height = %d, width = %d\n", x, y, height, width);
    while(i < height)
    {
        j = 0;
        while(j < width)
        {
            mlx_pixel_put(data->mlx, data->win, j + x, i + y, WHITE);
            j++;
        }
        i++;
    }
}