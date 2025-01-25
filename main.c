/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachid <rachid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:09:58 by reddamss          #+#    #+#             */
/*   Updated: 2025/01/25 11:44:20 by rachid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Headers/cub3d.h"
//x -> -- horizontal , y = | vertical

int get_plyr_pos(t_game *data)
{
    int	x;
	int	y;

	y = 0;
    printf("height of map%d\n", data->map_height);
	while (y < data->map_height)//is small than the height
	{
		x = 0;
		while (x < data->map_width)//is small than the width
		{
            if(ft_strchr("NSEW", data->map[y][x]))
            {
                data->player->character = data->map[y][x];
                data->player->x = x * TILE + (TILE/2);
                data->player->y = y * TILE + (TILE/2);
                data->map[y][x] = '0';
            }
			x++;
		}
		y++;
	}
    return(-1);
}


void    set_direction(t_game *data)
{
    if(data->player->character == 'N')
        data->player->rotationAngle = (-PI / 2);
    else if(data->player->character == 'S')
        data->player->rotationAngle = (PI / 2);
    else if(data->player->character == 'E')
        data->player->rotationAngle = 0;
    else if(data->player->character == 'W')
        data->player->rotationAngle = PI;
}


void    init_player(t_game *data)
{
    t_player *dot;

    dot = malloc(sizeof(t_player ));
    dot->radius = TILE / 5;
    dot->turnDir = 0;
    dot->walkDir = 0;
    dot->sideDir = 0;
    dot->moveSpeed = 8.0;
    dot->rotationSpeed = 2 * (PI / 2);
    dot->line_lenght = 50;
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

    get_plyr_pos(data);
    set_direction(data);



}





int main(int ac, char **av)
{
  	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
    if(!game)
        return 1;
    game->texture = malloc(sizeof(t_texture));
    if(!game->texture)
    {
        return 1;   
    }
	if(ac != 2)
    {
		return (ft_putstr_fd("Error\nUsage : Cub3d map.cub\n", 2), free(game),1);
    }
    // t_image image;
    (void)ac;
    
    init_player(game);//init dakchi d lplayer kamlo hna
    parse_config(game, av);
    init_ray(game);
    
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, S_WIDTH, S_HEIGHT, "gta");

    game->texture->img = mlx_xpm_file_to_image(game->mlx,"./Textures/face.xpm",&game->texture->tex_width, &game->texture->tex_height);
    if(!game->texture->img)
        return(2);
    game->texture->tex_data = (unsigned int *)mlx_get_data_addr(game->texture->img, &game->texture->bpp, &game->texture->size_line, &game->texture->endian);
    // printf("bpp =  %d, size_line = %d, endian = %d\n", game->bpp, game->size_line, game->endian);
    // draw_map(game);
 
    game->img = malloc(sizeof(t_image));
    if(!game->img)
        return 1;
        
    mlx_loop_hook(game->mlx, (void *)game_loop, game);//rsm lmap o zid lplayer o fov flkher d lfunction
    // mlx_loop_hook()
    mlx_hook(game->win, 2, (1L << 0), player_control, game);
    mlx_hook(game->win, 3, (1L << 1), key_release, game);
    mlx_loop(game->mlx);
    free_all(game);
}
    // (void)ac;
    // (void)av;o ft_memchr.o ft_itoa.o ft_isprint.o ft_isdigit.o ft_striteri.o ft_putL