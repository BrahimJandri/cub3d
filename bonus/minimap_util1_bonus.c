/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_util1_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reddamss <reddamss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:21:09 by bjandri           #+#    #+#             */
/*   Updated: 2025/02/08 08:57:56 by reddamss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Headers/cub3d_bonus.h"

void	draw_background(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y <= game->minimap->minimap_size)
	{
		x = 0;
		while (x <= game->minimap->minimap_size)
		{
			my_mlx_pixel_put(game, MINIMAP_X + x, MINIMAP_Y + y, WHITE);
			x++;
		}
		y++;
	}
}

void	my_mlx_pixel_put_safe(t_game *data, int x, int y, int color)
{
	if (x >= MINIMAP_X && x < MINIMAP_X + data->minimap->minimap_size && y >= MINIMAP_Y
		&& y < MINIMAP_Y + data->minimap->minimap_size)
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

	player_x = MINIMAP_X + (game->minimap->minimap_size / 2);
	player_y = MINIMAP_Y + (game->minimap->minimap_size / 2);
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
					RED);
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

	game->minimap->start_x = MINIMAP_X + (game->minimap->minimap_size / 2);
	game->minimap->start_y = MINIMAP_Y + (game->minimap->minimap_size / 2);
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
		my_mlx_pixel_put_safe(game, round(x), round(y), RED);
		x += game->minimap->xinc;
		y += game->minimap->yinc;
		i++;
	}
}
