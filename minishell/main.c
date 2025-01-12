/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reddamss <reddamss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:09:58 by reddamss          #+#    #+#             */
/*   Updated: 2025/01/12 11:38:43 by reddamss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Headers/cub3d.h"
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
                my_mlx_pixel_put(data, player->x + x, player->y + y, RED);
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

// int get_plyr_y(t_game *data)
// {
//     int	x;
// 	int	y;

// 	y = 0;
// 	while (y < data->map_y)//is small than the height
// 	{
// 		x = 0;
// 		while (x < data->map_x - 1)//is small than the width
// 		{
//             if(data->map[y][x] == 'P')
//                 return(y * TILE + (TILE/2));
// 			x++;
// 		}
// 		y++;
// 	}
//     return(-1);
// }
// int get_plyr_x(t_game *data)
// {
//     int	x;
// 	int	y;

// 	y = 0;
// 	while (y < data->map_y)//is small than the height
// 	{
// 		x = 0;
// 		while (x < data->map_x - 1)//is small than the width
// 		{
//             if(data->map[y][x] == 'P')
//             {
//                 data->map[y][x] = '0';
//                 return(x * TILE + (TILE/2));
//             }
// 			x++;
// 		}
// 		y++;
// 	}
//     return(-1);
// }


void    init_player(t_game *data)
{
    t_player *dot;

    dot = malloc(sizeof(t_player ));
    dot->y = 0;
    dot->x = 0;
    dot->radius = TILE / 5;
    dot->turnDir = 0;
    dot->walkDir = 0;
    dot->rotationAngle = PI / 2;
    dot->moveSpeed = 4.0;
    dot->rotationSpeed = 2 * (PI / 2);
    dot->line_lenght = 50 ;

    data->player = dot;
    data->num_rays = S_WIDTH / WALL_WIDTH ;

    
    
}


void    init_ray(t_game *data)
{
    t_ray *raay = malloc(sizeof(t_ray) * data->num_rays);
    if(!raay)
        return ;
    data->ray = raay;
}

void	error_msg(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}

int main(int ac, char **av)
{
  	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	if (ac != 2)
		return (ft_putstr_fd("Error\nUsage : Cub3d map.cub\n", 2), free(game),
			1);
    // t_image image;
    (void)ac;
    (void)av;
    
    // read_map(av[1], &data);
    // allocate_map(av[1], &data);
    init_player(game);//init dakchi d lplayer kamlo hna
    parse_config(game, av);

    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, S_WIDTH, S_HEIGHT, "gta");
    init_ray(game);

 
    mlx_loop_hook(game->mlx, (void *)draw_map, game);//rsm lmap o zid lplayer o fov flkher d lfunction
    // draw_rectangle(&data, 100, 200);
    // mlx_loop_hook()
    mlx_hook(game->win, 03, 1L<<1, key_release, game);
    mlx_hook(game->win, 02, 1L<<0, player_control, game);
    mlx_loop(game->mlx);
    free_all(game);
}
    // (void)ac;
    // (void)av;o ft_memchr.o ft_itoa.o ft_isprint.o ft_isdigit.o ft_striteri.o ft_putL