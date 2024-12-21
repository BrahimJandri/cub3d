/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reddamss <reddamss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:51:09 by reddamss          #+#    #+#             */
/*   Updated: 2024/11/14 11:01:28 by reddamss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int close_game(int key)
{
    if(key == ESC || key == Q)
        exit(0);
    return 0;
}

int    cross_close(void)
{
    printf("Window closed !!\n");
    exit(0);
    return 0;
}
void    update(t_game *data)
{
    data->x += 1;
    data->y += 1;
}

// void    free_all()
// {
    
// }

int main(int ac, char **av)
{
    t_game data;
    t_player *player;
    // int x, y;
    
    (void)av;
    (void)player;   
    if(ac != 2)
        exit_mssg("Arguments Not Valid");     
    
    data.y = 0;
    data.x = 0;
    read_map(av[1], &data);
    allocate_map(av[1], &data);
    create_player(&data);
    data.mlx_ptr = mlx_init();
    data.win_ptr = mlx_new_window(data.mlx_ptr, (S_W *(data.map_y - 1)), (data.map_x * S_H), "tol3ibt");
    // data.win_ptr = mlx_new_window(data.mlx_ptr, 400, 280, "tol3ibt");
    
    
    // while(1)
    // {
    //     build_square(&data, data.x, data.y, RED);
    //     update(&data);
    //     usleep(10000);
    //     mlx_clear_window(data.mlx_ptr, data.win_ptr);
    // }
    
    draw_map(&data);
    
    // player = data.user;
    // draw_circle(data.img_ptr, data.win_ptr, 100, 80, 8, RED);

    // build_square(&data, 400/2, 280 /2, RED);
    

    mlx_key_hook(data.win_ptr, close_game, NULL);
    // mlx_hook(data.win_ptr, 02,1L<<0, move_player, &data);
    mlx_hook(data.win_ptr, 17,0, cross_close, NULL);

    
    mlx_loop(data.mlx_ptr);
    // free_all(&data);
}