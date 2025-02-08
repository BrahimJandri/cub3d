/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_walls_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachid <rachid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:50:53 by rachid            #+#    #+#             */
/*   Updated: 2025/02/08 14:36:28 by rachid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Headers/cub3d_bonus.h"




void	my_mlx_pixel_put(t_game *data, int x, int y, int color)
{
	char	*dst;
    
    if (x < 0 || x >= S_WIDTH || y < 0 || y >= S_HEIGHT) {
        return;
    }

	dst = data->img->addrs + (y * data->img->size_line + x * (data->img->bpp / 8));

	*(unsigned int*)dst = color;
}

void put_floor(t_game *data, int wall_bottom, int i)
{
    int j;
    double distance;

    j = wall_bottom;
    while (j < S_HEIGHT)
    {
        distance = (j - S_HEIGHT / 2) / (double)(S_HEIGHT / 2);
        distance = 1 / (distance);
        my_mlx_pixel_put(data, i * WALL_WIDTH, j++, data->floor_color);
    }
}

void put_ceiling(t_game *data, int walltop, int i)
{
    int j;
    double distance;

    j = 0;
    while (j < walltop)
    {
        distance = (S_HEIGHT / 2 - j) / (S_HEIGHT / 2);
        distance = 1 / (distance);
        my_mlx_pixel_put(data, i * WALL_WIDTH, j++, data->ceiling_color);
    }
}

void    put_wall(t_game *data, int  wall_top, int wall_bottom, int i)
{
    int j;

    j = wall_top;
    while (j < wall_bottom)
    {
        get_texture(data, j);
        my_mlx_pixel_put(data, i * WALL_WIDTH, j++, data->color);
    }
}