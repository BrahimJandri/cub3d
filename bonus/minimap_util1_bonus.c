/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_util1_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:21:09 by bjandri           #+#    #+#             */
/*   Updated: 2025/02/03 11:43:14 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Headers/cub3d_bonus.h"

void	build_square(t_game *data, int x, int y, int color)
{
	int	tile_size;
	int	i;
	int	j;

	i = 0;
	tile_size = TILE * MINIMAP;
	while (i < tile_size)
	{
		j = 0;
		while (j < tile_size)
		{
			my_mlx_pixel_put(data, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_background(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < MINIMAP_SIZE)
	{
		x = 0;
		while (x < MINIMAP_SIZE)
		{
			my_mlx_pixel_put(game, MINIMAP_X + x, MINIMAP_Y + y, 0x000000);
			x++;
		}
		y++;
	}
}

void	my_mlx_pixel_put_safe(t_game *data, int x, int y, int color)
{
	if (x >= MINIMAP_X && x < MINIMAP_X + MINIMAP_SIZE && y >= MINIMAP_Y
		&& y < MINIMAP_Y + MINIMAP_SIZE)
	{
		my_mlx_pixel_put(data, x, y, color);
	}
}

void	draw_minimap_player(t_game *game)
{
	int	player_x;
	int	player_y;
	int	radius;
	int	x;
	int	y;

	player_x = MINIMAP_X + (MINIMAP_SIZE / 2);
	player_y = MINIMAP_Y + (MINIMAP_SIZE / 2);
	radius = 3;
	x = -radius;
	while (x <= radius)
	{
		y = -radius;
		while (y <= radius)
		{
			if (x * x + y * y <= radius * radius)
			{
				my_mlx_pixel_put_safe(game, player_x + x, player_y + y,
					0xFF0000);
			}
			y++;
		}
		x++;
	}
}

void	draw_ray_line(t_game *game, int end_x, int end_y)
{
	double	x;
	double	y;
	int		i;

	game->minimap->start_x = MINIMAP_X + (MINIMAP_SIZE / 2);
	game->minimap->start_y = MINIMAP_Y + (MINIMAP_SIZE / 2);
	game->minimap->dx = end_x - game->minimap->start_x;
	game->minimap->dy = end_y - game->minimap->start_y;
	game->minimap->steps = fmax(fabs(game->minimap->dx),
			fabs(game->minimap->dy));
	game->minimap->xinc = game->minimap->dx / game->minimap->steps;
	game->minimap->yinc = game->minimap->dy / game->minimap->steps;
	x = game->minimap->start_x;
	y = game->minimap->start_y;
	i = 0;
	while (i <= game->minimap->steps)
	{
		my_mlx_pixel_put_safe(game, round(x), round(y), 0xFF0000);
		x += game->minimap->xinc;
		y += game->minimap->yinc;
		i++;
	}
}
