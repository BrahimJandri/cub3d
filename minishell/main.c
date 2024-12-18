/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reddamss <reddamss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:09:58 by reddamss          #+#    #+#             */
/*   Updated: 2024/12/18 11:17:54 by reddamss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//x -> -- horizontal , y = | vertical

void draw_circle(t_player *player, t_game *data, int _y, int _x) {
    int x, y;
    

    
    for (x = -player->radius; x <= player->radius; x++) 
    {
        for (y = -player->radius; y <= player->radius; y++)
        {
            // Check if the point (x, y) satisfies the circle equation
            if ((x * x + y * y) <= player->radius * player->radius)
            {
                mlx_pixel_put(data->mlx, data->win, _x + x, _y + y, RED);
            }
        }
    }
}



// void draw_circle(void *mlx, void *win, int center_x, int center_y, int radius, int color) {
//     int x, y;

//     for (x = -radius; x <= radius; x++) {
//         for (y = -radius; y <= radius; y++) {
//             // Check if the point (x, y) satisfies the circle equation
//             if ((x * x + y * y) <= radius * radius) {
//                 mlx_pixel_put(mlx, win, center_x + x, center_y + y, color);
//                 usleep(800);
//             }
//         }
//     }
// }


void    init_player(t_game *data)
{
    t_player *dot;

    dot = malloc(sizeof(t_player ));
    dot->y = 3;
    dot->x = 3;
    dot->radius = TILE / 4;
    dot->turnDir = 0;
    dot->walkDir = 0;
    dot->rotationAngle = PI / 2;
    dot->moveSpeed = 2.0;
    dot->rotationSpeed = 2 * (PI / 2);

    data->player = dot;


}


int main(int ac, char **av)
{
    t_game data;

    (void)ac;
    (void)av;
    
    read_map(av[1], &data);
    allocate_map(av[1], &data);
    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, S_WIDTH, S_HEIGHT, "gta");
    init_player(&data);

    draw_map(&data);

    mlx_loop(data.mlx);
    
}
    // (void)ac;
    // (void)av;o ft_memchr.o ft_itoa.o ft_isprint.o ft_isdigit.o ft_striteri.o ft_put