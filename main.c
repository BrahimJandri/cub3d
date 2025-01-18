/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachid <rachid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:09:58 by reddamss          #+#    #+#             */
/*   Updated: 2025/01/19 00:07:26 by rachid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Headers/cub3d.h"
//x -> -- horizontal , y = | vertical

int get_plyr_pos(t_game *data)
{
    int	x;
	int	y;

	y = 0;
	while (y < data->map_height)//is small than the height
	{
		x = 0;
		while (x < data->map_width)//is small than the width
		{
            if(data->map[y][x] == 'N')
            {
                data->map[y][x] = '0';
                data->player->x = x * TILE + (TILE/2);
                data->player->y = y * TILE + (TILE/2);
            }
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
    dot->y = 0;
    dot->x = 0;
    dot->radius = TILE / 5;
    dot->turnDir = 0;
    dot->walkDir = 0;
    dot->rotationAngle = PI / 2;
    dot->moveSpeed = 4.0;
    dot->rotationSpeed = 2 * (PI / 2);
    dot->line_lenght = 50 ;
    dot->angle = 0;


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





int main(int ac, char **av)
{
  	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	if (ac != 2)
		return (ft_putstr_fd("Error\nUsage : Cub3d map.cub\n", 2), free(game),
			1);
    // t_image image;
    (void)ac;
    
    init_player(game);//init dakchi d lplayer kamlo hna
    parse_config(game, av);
    init_ray(game);
    
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, S_WIDTH, S_WIDTH, "gta");
    get_plyr_pos(game);

    game->wall_tex = mlx_xpm_file_to_image(game->mlx,"./Textures/cube_wall.xpm",&game->tex_width, &game->tex_height);
    if(!game->wall_tex)
        return(2);
    game->tex_data = (unsigned int *)mlx_get_data_addr(game->wall_tex, &game->bpp, &game->size_line, &game->endian);
    
    // draw_map(game);
 
    mlx_loop_hook(game->mlx, (void *)draw_map, game);//rsm lmap o zid lplayer o fov flkher d lfunction
    // mlx_loop_hook()
    // mlx_hook(game->win, 03, 1L<<1, key_release, game);
    mlx_hook(game->win, 02, 1L<<0, player_control, game);
    mlx_loop(game->mlx);
    free_all(game);
}
    // (void)ac;
    // (void)av;o ft_memchr.o ft_itoa.o ft_isprint.o ft_isdigit.o ft_striteri.o ft_putL