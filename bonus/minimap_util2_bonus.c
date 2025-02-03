/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_util2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:22:53 by bjandri           #+#    #+#             */
/*   Updated: 2025/02/03 11:33:12 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Headers/cub3d_bonus.h"

void draw_player_direction(t_game *game)
{
    int center_x; 
    int center_y;
    double ray_length; 
    int i;
    int end_x;
    int end_y;
    double ray_angle;
    
    center_x = MINIMAP_X + (MINIMAP_SIZE / 2);
    center_y = MINIMAP_Y + (MINIMAP_SIZE / 2);
    ray_length = MINIMAP_SIZE / 8;
    i = -30;

    while (i <= 30)
    {
        ray_angle = game->player->rotationAngle + (i * FOV / 60);
        end_x = center_x + cos(ray_angle) * ray_length;
        end_y = center_y + sin(ray_angle) * ray_length;
        draw_ray_line(game, end_x, end_y);
        i++;
    }
}

void draw_map_mini(t_game *data)
{
    int visible_range = 5;
    int player_map_x = data->player->x / TILE;
    int player_map_y = data->player->y / TILE;
    int dy = -visible_range;
    int dx;

    while (dy <= visible_range)
    {
        dx = -visible_range;
        while (dx <= visible_range)
        {
            draw_tile_within_bounds(data, player_map_x + dx, player_map_y + dy);
            dx++;
        }
        dy++;
    }
}

int get_tile_color(char cell)
{
    if (cell == '1')
        return 0x606060; // Wall color
    else if (cell == '0' || ft_strchr("NSEW", cell))
        return WHITE; // Floor or player spawn color
    else if (cell == 'D')
        return 0x4278F5; // Door color
    return -1; // Invalid cell
}

void calculate_tile_position(t_game *data, int map_x, int map_y, int *tile_x, int *tile_y)
{
    float player_map_x; 
    float player_map_y; 
    float offset_x; 
    float offset_y;
    
    player_map_x = data->player->x / TILE;
    player_map_y = data->player->y / TILE;
    offset_x = (data->player->x - (int)(player_map_x * TILE)) * MINIMAP;
    offset_y = (data->player->y - (int)(player_map_y * TILE)) * MINIMAP;

    *tile_x = MINIMAP_X + (MINIMAP_SIZE / 2) + (map_x - player_map_x) * (TILE * MINIMAP) - offset_x;
    *tile_y = MINIMAP_Y + (MINIMAP_SIZE / 2) + (map_y - player_map_y) * (TILE * MINIMAP) - offset_y;
}

void draw_tile(t_game *data, int tile_x, int tile_y, int color)
{
    int tile_size;
    int pixel_x;
    int pixel_y;
    
    tile_size = TILE * MINIMAP;

    for (int i = 0; i < tile_size; i++)
    {
        for (int j = 0; j < tile_size; j++)
        {
            pixel_x = tile_x + i;
            pixel_y = tile_y + j;
            if (pixel_x >= MINIMAP_X && pixel_x < MINIMAP_X + MINIMAP_SIZE &&
            pixel_y >= MINIMAP_Y && pixel_y < MINIMAP_Y + MINIMAP_SIZE)
            {
                my_mlx_pixel_put(data, pixel_x, pixel_y, color);
            }
        }
    }
}
