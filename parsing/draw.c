/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 10:46:04 by bjandri           #+#    #+#             */
/*   Updated: 2024/12/24 11:29:06 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"


void	draw_rectangle(t_game *game, int x, int y, int color)
{
	int i, j;
	int start_x = x * TILE_SIZE;
	int start_y = y * TILE_SIZE;

	for (i = 0; i < TILE_SIZE; i++)
	{
		for (j = 0; j < TILE_SIZE; j++)
		{
			mlx_pixel_put(game->mlx, game->win, start_x + j, start_y + i, color);
		}
	}
}

void	draw_map(t_game *game)
{
	int x, y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == '1') // Wall
				draw_rectangle(game, x, y, 0x0000ff); // Black
			else if (game->map[y][x] == '0') // Open space
				draw_rectangle(game, x, y, 0xFFFFFF); // White
			else if (game->map[y][x] == 'N' || game->map[y][x] == 'S' || 
					 game->map[y][x] == 'E' || game->map[y][x] == 'W') // Player
			{
				draw_rectangle(game, x, y, 0x00FF00); // Green for player
				// Optionally draw a direction line
				mlx_pixel_put(game->mlx, game->win, 
							  x * TILE_SIZE + TILE_SIZE / 2, 
							  y * TILE_SIZE + TILE_SIZE / 2, 0xFF0000); // Red
			}
			x++;
		}
		y++;
	}
}

