/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:01:18 by rachid            #+#    #+#             */
/*   Updated: 2025/02/03 11:36:38 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Headers/cub3d_bonus.h"

void	draw_tile_within_bounds(t_game *data, int map_x, int map_y)
{
	char	cell;
	int		color;

	if (map_x < 0 || map_y < 0 || map_y >= data->map_height
		|| map_x >= data->map_width)
		return ;
	cell = data->map[map_y][map_x];
	color = get_tile_color(cell);
	if (color == -1)
		return ;
	calculate_tile_position(data, map_x, map_y);
	if (data->minimap->tile_x + (TILE * MINIMAP) > MINIMAP_X
		&& data->minimap->tile_x < MINIMAP_X + MINIMAP_SIZE
		&& data->minimap->tile_y + (TILE * MINIMAP) > MINIMAP_Y
		&& data->minimap->tile_y < MINIMAP_Y + MINIMAP_SIZE)
	{
		draw_tile(data, color);
	}
}

void	update_minimap(t_game *data)
{
	static int	frame;

	frame = 0;
	if (frame % 1 == 0)
	{
		draw_minimap(data);
	}
	frame++;
}

void	init_minimap(t_game *game)
{
	t_minimap	*minimap;

	minimap = malloc(sizeof(t_minimap));
	minimap->dx = 0;
	minimap->dy = 0;
	minimap->start_x = 0;
	minimap->start_y = 0;
	minimap->steps = 0;
	minimap->xinc = 0;
	minimap->yinc = 0;
	minimap->center_x = 0;
	minimap->center_y = 0;
	minimap->ray_angle = 0;
	minimap->ray_length = 0;
	minimap->visible_range = 0;
	minimap->player_map_x = 0;
	minimap->player_map_y = 0;
	minimap->tile_x = 0;
	minimap->tile_y = 0;
	game->minimap = minimap;
}

void	draw_minimap(t_game *game)
{
	init_minimap(game);
	mlx_clear_window(game->mlx, game->win);
	draw_background(game);
	draw_map_mini(game);
	draw_minimap_player(game);
	draw_player_direction(game);
}
