/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getting_data_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:23:27 by rachid            #+#    #+#             */
/*   Updated: 2025/02/06 11:01:35 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Headers/cub3d_bonus.h"

void get_data(t_game *data)
{
    if (data->player->walkDir)
    {
        update_player(data, data->player);
    }
    if (data->player->turnDir)
    {
        data->player->rotationAngle += data->player->turnDir * data->player->rotationSpeed;
    }
    if (data->player->sideDir)
    {
        update_sides(data, data->player);
    }
    return;
}

int get_color(t_texture *texture, int x, int y)
{
    unsigned int color;

    color = *(int *)(texture->addrs + (y * texture->size_line) + x * (texture->bpp / 8));

    return color;
}

// array: 0 = so, 1 = no, 2 = we, 3 = ea;

void get_the_right_color(t_game *data, int offset_x, int offset_y)
{
    if (!data->ray->is_vert && !data->ray->ray_down)
        data->color = get_color(data->texture[1], offset_x, offset_y);

    if (!data->ray->is_vert && data->ray->ray_down)
        data->color = get_color(data->texture[0], offset_x, offset_y);

    if (data->ray->is_vert && !data->ray->ray_right)
        data->color = get_color(data->texture[2], offset_x, offset_y);

    if (data->ray->is_vert && data->ray->ray_right)
        data->color = get_color(data->texture[3], offset_x, offset_y);
}

void get_texture(t_game *data, int j)
{
    int offset_x;
    int offset_y;
    int distance_from_top;

    if (data->ray->is_vert)
        offset_x = (int)data->ray->y_wall % TILE;
    else
        offset_x = (int)data->ray->x_wall % TILE;

    distance_from_top = j + (data->wall_projected_height / 2) - (S_HEIGHT / 2);
    offset_y = distance_from_top * ((double)TILE / data->wall_projected_height);

    if ((offset_x >= 0 && offset_x < TILE) && (offset_y >= 0 && offset_y < TILE))
    {
        get_the_right_color(data, offset_x, offset_y);
    }
}

int game_loop(t_game *data)
{
    get_data(data);
    draw_map(data);
    return (0);
}