/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_util2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachid <rachid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:22:53 by bjandri           #+#    #+#             */
/*   Updated: 2025/02/07 11:31:12 by rachid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Headers/cub3d_bonus.h"

void	draw_player_direction(t_game *game)
{
	int	i;
	int	end_x;
	int	end_y;

	game->minimap->center_x = MINIMAP_X + (MINIMAP_SIZE / 2);
	game->minimap->center_y = MINIMAP_Y + (MINIMAP_SIZE / 2);
	game->minimap->ray_length = MINIMAP_SIZE / 8;
	i = -30;
	while (i <= 30)
	{
		game->minimap->ray_angle = game->player->rotationAngle + (i * FOV / 60);
		end_x = game->minimap->center_x + cos(game->minimap->ray_angle)
			* game->minimap->ray_length;
		end_y = game->minimap->center_y + sin(game->minimap->ray_angle)
			* game->minimap->ray_length;
		draw_ray_line(game, end_x, end_y);
		i++;
	}
}

void	draw_map_mini(t_game *data)
{
	int	dy;
	int	dx;

	data->minimap->visible_range = 5;
	data->minimap->player_map_x = data->player->x / TILE;
	data->minimap->player_map_y = data->player->y / TILE;
	dy = -data->minimap->visible_range;
	while (dy <= data->minimap->visible_range)
	{
		dx = -data->minimap->visible_range;
		while (dx <= data->minimap->visible_range)
		{
			draw_tile_within_bounds(data, data->minimap->player_map_x + dx,
				data->minimap->player_map_y + dy);
			dx++;
		}
		dy++;
	}
}

int	get_tile_color(char cell)
{
	if (cell == '1')
		return (GREY);
	else if (cell == '0' || ft_strchr("NSEW", cell))
		return (WHITE);
	return (-1);
}

void	calculate_tile_position(t_game *data, int map_x, int map_y)
{
	double	player_map_x;
	double	player_map_y;
	double	offset_x;
	double	offset_y;

	player_map_x = data->player->x / TILE;
	player_map_y = data->player->y / TILE;
	offset_x = (data->player->x - (player_map_x * TILE)) * MINIMAP;
	offset_y = (data->player->y - (player_map_y * TILE)) * MINIMAP;
	data->minimap->tile_x = MINIMAP_X + (MINIMAP_SIZE / 2) + (map_x
			- player_map_x) * (TILE * MINIMAP) - offset_x;
	data->minimap->tile_y = MINIMAP_Y + (MINIMAP_SIZE / 2) + (map_y
			- player_map_y) * (TILE * MINIMAP) - offset_y;
}

void	draw_tile(t_game *data, int color)
{
	int	tile_size;
	int	pixel_x;
	int	pixel_y;
	int	i;
	int	j;

	tile_size = TILE * MINIMAP;
	i = 0;
	while (i < tile_size)
	{
		j = 0;
		while (j < tile_size)
		{
			pixel_x = data->minimap->tile_x + i;
			pixel_y = data->minimap->tile_y + j;
			if (pixel_x >= MINIMAP_X && pixel_x < MINIMAP_X + MINIMAP_SIZE
				&& pixel_y >= MINIMAP_Y && pixel_y < MINIMAP_Y + MINIMAP_SIZE)
			{
				my_mlx_pixel_put(data, pixel_x, pixel_y, color);
			}
			j++;
		}
		i++;
	}
}
