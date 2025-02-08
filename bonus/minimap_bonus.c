/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reddamss <reddamss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:01:18 by rachid            #+#    #+#             */
/*   Updated: 2025/02/08 08:56:24 by reddamss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Headers/cub3d_bonus.h"

void	draw_tile_within_bounds(t_game *data, int map_x, int map_y)
{
	char	cell;
	int		color;
	double	minimap;

	minimap = data->minimap->minimap_size;
	if (map_x < 0 || map_y < 0 || map_y >= data->map_height
		|| map_x >= data->map_width)
		return ;
	cell = data->map[map_y][map_x];
	color = get_tile_color(cell);
	if (color == -1)
		return ;
	calculate_tile_position(data, map_x, map_y);
	if (data->minimap->tile_x + (TILE * MINIMAP) > MINIMAP_X
		&& data->minimap->tile_x < MINIMAP_X + minimap && data->minimap->tile_y
		+ (TILE * MINIMAP) > MINIMAP_Y && data->minimap->tile_y < MINIMAP_Y
		+ minimap)
	{
		draw_tile(data, color);
	}
}

void	init_minimap(t_game *game)
{
	t_minimap	*minimap;

	minimap = malloc(sizeof(t_minimap));
	if (!minimap)
		error_msg("minimap failed\n");
	ft_memset(minimap, 0, sizeof(minimap));
	minimap->minimap_size = (S_WIDTH / 16 + S_HEIGHT / 16);
	game->minimap = minimap;
}

void	draw_minimap(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	draw_background(game);
	draw_map_mini(game);
	draw_minimap_player(game);
	draw_player_direction(game);
}
