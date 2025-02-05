/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachid <rachid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:01:18 by rachid            #+#    #+#             */
/*   Updated: 2025/02/05 09:49:39 by rachid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Headers/cub3d_bonus.h"

static bool is_within_minimap(int x, int y)
{
    return (x >= MINIMAP_X && x < MINIMAP_X + MINIMAP_SIZE &&
            y >= MINIMAP_Y && y < MINIMAP_Y + MINIMAP_SIZE);
}

void build_square(t_game *data, int x, int y, int color)
{
    int tile_size = TILE * MINIMAP;
    int i = 0;
    int j;

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

void draw_background(t_game *game)
{
    int y = 0;
    int x;

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

void my_mlx_pixel_put_safe(t_game *data, int x, int y, int color)
{
    if (is_within_minimap(x, y))
    {
        my_mlx_pixel_put(data, x, y, color);
    }
}

void draw_minimap_player(t_game *game)
{
    int player_x = MINIMAP_X + (MINIMAP_SIZE / 2);
    int player_y = MINIMAP_Y + (MINIMAP_SIZE / 2);
    int radius = 3;
    int x = -radius;
    int y;

    while (x <= radius)
    {
        y = -radius;
        while (y <= radius)
        {
            if (x * x + y * y <= radius * radius)
            {
                my_mlx_pixel_put_safe(game, player_x + x, player_y + y, 0xFF0000);
            }
            y++;
        }
        x++;
    }
}

void draw_ray_line(t_game *game, int end_x, int end_y)
{
    int start_x = MINIMAP_X + (MINIMAP_SIZE / 2);
    int start_y = MINIMAP_Y + (MINIMAP_SIZE / 2);

    double dx = end_x - start_x;
    double dy = end_y - start_y;
    double steps = fmax(fabs(dx), fabs(dy));
    double xinc = dx / steps;
    double yinc = dy / steps;
    double x = start_x;
    double y = start_y;
    int i = 0;

    while (i <= steps)
    {
        my_mlx_pixel_put_safe(game, round(x), round(y), 0xFF0000);
        x += xinc;
        y += yinc;
        i++;
    }
}

void draw_player_direction(t_game *game)
{
    int center_x = MINIMAP_X + (MINIMAP_SIZE / 2);
    int center_y = MINIMAP_Y + (MINIMAP_SIZE / 2);
    double ray_length = MINIMAP_SIZE / 8;
    int i = -30;

    while (i <= 30)
    {
        double ray_angle = game->player->rotationAngle + (i * FOV / 60);
        int end_x = center_x + cos(ray_angle) * ray_length;
        int end_y = center_y + sin(ray_angle) * ray_length;
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

void draw_tile_within_bounds(t_game *data, int map_x, int map_y)
{
    int color;
    int tile_size = TILE * MINIMAP;

    if (map_x < 0 || map_y < 0 || map_y >= data->map_height || map_x >= data->map_width)
        return;

    char cell = data->map[map_y][map_x];
    if (cell == '1')
        color = 0x606060;
    else if (cell == '0' || ft_strchr("NSEW", cell))
        color = WHITE;
    else if (cell == 'D')
        color = 0x4278F5;
    else
        return;

    float player_map_x = data->player->x / TILE;
    float player_map_y = data->player->y / TILE;
    float offset_x = (data->player->x - (int)(player_map_x * TILE)) * MINIMAP;
    float offset_y = (data->player->y - (int)(player_map_y * TILE)) * MINIMAP;

    int tile_x = MINIMAP_X + (MINIMAP_SIZE / 2) + (map_x - player_map_x) * tile_size - offset_x;
    int tile_y = MINIMAP_Y + (MINIMAP_SIZE / 2) + (map_y - player_map_y) * tile_size - offset_y;

    if (tile_x + tile_size > MINIMAP_X && tile_x < MINIMAP_X + MINIMAP_SIZE &&
        tile_y + tile_size > MINIMAP_Y && tile_y < MINIMAP_Y + MINIMAP_SIZE)
    {
        int i = 0;
        int j;
        while (i < tile_size)
        {
            j = 0;
            while (j < tile_size)
            {
                int pixel_x = tile_x + i;
                int pixel_y = tile_y + j;
                if (is_within_minimap(pixel_x, pixel_y))
                {
                    my_mlx_pixel_put(data, pixel_x, pixel_y, color);
                }
                j++;
            }
            i++;
        }
    }
}

void update_minimap(t_game *data)
{
    static int frame = 0;
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


