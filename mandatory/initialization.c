/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:18:54 by rachid            #+#    #+#             */
/*   Updated: 2025/02/09 11:51:40 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Headers/cub3d.h"

void	inits(t_game *game, char **av)
{
	init_player(game);
	parse_config(game, av);
	init_ray(game);
	init_mlx(game);
	get_textures(game);
}

void	init_player(t_game *data)
{
	t_player	*dot;

	dot = malloc(sizeof(t_player));
	dot->radius = TILE / 5;
	dot->turn_dir = 0;
	dot->walk_dir = 0;
	dot->side_dir = 0;
	dot->move_speed = 2;
	dot->rotation_speed = 0.5 * (PI / 2);
	dot->fov = FOV * (PI / 180);
	data->player = dot;
	data->num_rays = S_WIDTH / WALL_WIDTH;
}

void	init_ray(t_game *data)
{
	t_ray	*raay;

	raay = malloc(sizeof(t_ray) * data->num_rays);
	if (!raay)
		error_msg("num rays failed\n");
	data->ray = raay;
	get_plyr_pos(data);
	set_direction(data);
}

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		error_msg("mlx_init failed\n");
	game->win = mlx_new_window(game->mlx, S_WIDTH, S_HEIGHT, "CUB3D");
	if (!game->win)
		error_msg("win failed\n");
}
