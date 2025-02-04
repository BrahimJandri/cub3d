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

void draw_tile_within_bounds(t_game *data, int map_x, int map_y)
{
    if (map_x < 0 || map_y < 0 || map_y >= data->map_height || map_x >= data->map_width)
        return;

    char cell; 
    int color;
    int tile_x;
    int tile_y;

    cell = data->map[map_y][map_x];
    color = get_tile_color(cell);
    if (color == -1)
        return;

    calculate_tile_position(data, map_x, map_y, &tile_x, &tile_y);

    if (tile_x + (TILE * MINIMAP) > MINIMAP_X && tile_x < MINIMAP_X + MINIMAP_SIZE &&
        tile_y + (TILE * MINIMAP) > MINIMAP_Y && tile_y < MINIMAP_Y + MINIMAP_SIZE)
    {
        draw_tile(data, tile_x, tile_y, color);
    }
}

void update_minimap(t_game *data)
{
    static int frame;
    
    frame = 0;
    if (frame % 1 == 0)
    {
        draw_minimap(data);
    }
    frame++;
}

void draw_minimap(t_game *game)
{
    mlx_clear_window(game->mlx, game->win);
    draw_background(game);
    draw_map_mini(game);
    draw_minimap_player(game);
    draw_player_direction(game);
}