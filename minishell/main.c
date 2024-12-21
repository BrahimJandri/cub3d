/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reddamss <reddamss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:09:58 by reddamss          #+#    #+#             */
/*   Updated: 2024/12/21 10:26:38 by reddamss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//x -> -- horizontal , y = | vertical

void draw_circle(t_player *player, t_game *data) {
    int x, y;
    

    
    for (x = -player->radius; x <= player->radius; x++) 
    {
        for (y = -player->radius; y <= player->radius; y++)
        {
            // Check if the point (x, y) satisfies the circle equation
            if ((x * x + y * y) <= player->radius * player->radius)
            {
                mlx_pixel_put(data->mlx, data->win, player->x + x, player->y + y, RED);
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

int get_plyr_y(t_game *data)
{
    int	x;
	int	y;

	y = 0;
	while (y < data->map_y)//is small than the height
	{
		x = 0;
		while (x < data->map_x - 1)//is small than the width
		{
            if(data->map[y][x] == 'P')
                return(y * TILE + (TILE/2));
			x++;
		}
		y++;
	}
    return(-1);
}
int get_plyr_x(t_game *data)
{
    int	x;
	int	y;

	y = 0;
	while (y < data->map_y)//is small than the height
	{
		x = 0;
		while (x < data->map_x - 1)//is small than the width
		{
            if(data->map[y][x] == 'P')
                return(x * TILE + (TILE/2));
			x++;
		}
		y++;
	}
    return(-1);
}


void    init_player(t_game *data)
{
    t_player *dot;

    dot = malloc(sizeof(t_player ));
    dot->y = get_plyr_y(data);
    dot->x = get_plyr_x(data);
    dot->radius = TILE / 5;
    dot->turnDir = 0;
    dot->walkDir = 0;
    dot->rotationAngle = PI /2;
    dot->moveSpeed = 4.0;
    dot->rotationSpeed = 2 * (PI / 2);
    dot->line_lenght = TILE ;

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
    init_player(&data);//init dakchi d lplayer kamlo hna

    draw_map(&data);//rsm lmap o zid lplayer o fov flkher d lfunction
    
    mlx_hook(data.win, 02, 1L<<0, player_control, &data);
    mlx_loop(data.mlx);
    
}
    // (void)ac;
    // (void)av;o ft_memchr.o ft_itoa.o ft_isprint.o ft_isdigit.o ft_striteri.o ft_put