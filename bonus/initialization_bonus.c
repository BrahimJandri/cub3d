/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachid <rachid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:18:54 by rachid            #+#    #+#             */
/*   Updated: 2025/02/05 10:22:40 by rachid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Headers/cub3d_bonus.h"

void    inits(t_game *game, char **av)
{
    init_player(game);//init dakchi d lplayer kamlo hna
    parse_config(game, av);
    init_ray(game);
    init_sprites(game);
    alloc_doors(game);
    init_door(game);
    init_mlx(game);
    get_textures(game);
    
}
void    init_player(t_game *data)
{
    t_player *dot;

    dot = malloc(sizeof(t_player ));
    dot->radius = TILE / 5;
    dot->turnDir = 0;
    dot->walkDir = 0;
    dot->sideDir = 0;
    dot->moveSpeed = 8;
    dot->rotationSpeed = 1 * (PI / 2);
    dot->line_lenght = 50;
    dot->angle = 0;
    dot->frames = 0;
    dot->bullets = 0;

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


void    init_mlx(t_game *game)
{
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, S_WIDTH, S_HEIGHT, "gta");
}

void    inits(t_game *game, char **av)
{
    init_player(game);//init dakchi d lplayer kamlo hna
    parse_config(game, av);
    init_ray(game);
    init_sprites(game);
    alloc_doors(game);
    init_door(game);
    init_mlx(game);
    get_textures(game);
    
}
