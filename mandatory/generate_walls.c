/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_walls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:02:34 by bjandri           #+#    #+#             */
/*   Updated: 2025/02/08 19:05:16 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Headers/cub3d.h"

void	my_mlx_pixel_put(t_game *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= S_WIDTH || y < 0 || y >= S_HEIGHT)
	{
		return ;
	}
	dst = data->img->addrs + (y * data->img->size_line + x * (data->img->bpp
				/ 8));
	*(unsigned int *)dst = color;
}

void	put_floor(t_game *data, int wall_bottom, int i)
{
	int	j;

	j = wall_bottom;
	while (j < S_HEIGHT)
		my_mlx_pixel_put(data, i * WALL_WIDTH, j++, data->floor_color);
}

void	put_ceiling(t_game *data, int walltop, int i)
{
	int	j;

	j = 0;
	while (j < walltop)
		my_mlx_pixel_put(data, i * WALL_WIDTH, j++, data->ceiling_color);
}

void	put_wall(t_game *data, int wall_top, int wall_bottom, int i)
{
	int	j;

	j = wall_top;
	while (j < wall_bottom)
	{
		get_texture(data, j);
		my_mlx_pixel_put(data, i * WALL_WIDTH, j++, data->color);
	}
}
