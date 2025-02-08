/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachid <rachid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:04:23 by reddamss          #+#    #+#             */
/*   Updated: 2025/02/08 16:24:37 by rachid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Headers/cub3d_bonus.h"

void	draw_map(t_game *data)
{
	data->img->img = mlx_new_image(data->mlx, S_WIDTH, S_HEIGHT);
	if (!data->img->img)
	{
		mlx_destroy_image(data->mlx, data->img->img);
		free_parse(data);
		free(data->minimap);
		destroy_sprite(data);
		escape_free(data);
		free(data);
		error_msg("Img failed\n");
	}
	data->img->addrs = mlx_get_data_addr(data->img->img, &data->img->bpp,
			&data->img->size_line, &data->img->endian);
	if (!data->img->addrs)
	{
		mlx_destroy_image(data->mlx, data->img->img);
		escape_free(data);
		free_all(data);
		error_msg("Img failed\n");
	}
	draw_rays(data->player, data);
	draw_minimap(data);
	render_gun(data);
	put_gun(data, data->player->frames);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	mlx_destroy_image(data->mlx, data->img->img);
}

void	render_image(t_game *data, int wallTopPixel, int wallBottomPixel, int i)
{
	put_ceiling(data, wallTopPixel, i);
	put_wall(data, wallTopPixel, wallBottomPixel, i);
	put_floor(data, wallBottomPixel, i);
}

void	draw_rays(t_player *player, t_game *data)
{
	double	ray_angle;
	double	angle_increment;
	int		wall_top_pixel;
	int		wall_bottom_pixel;
	int		i;

	angle_increment = player->fov / data->num_rays;
	ray_angle = player->rotation_angle - (player->fov / 2);
	i = -1;
	while (++i < data->num_rays)
	{
		cast_rays(player, data, ray_angle);
		data->corrected_wall = data->ray->distance * cos(ray_angle
				- player->rotation_angle);
		data->distance_projectplan = (S_WIDTH / 2) / tan(player->fov / 2);
		data->wall_projected_height = (TILE / data->corrected_wall)
			* data->distance_projectplan;
		wall_top_pixel = (S_HEIGHT / 2) - (data->wall_projected_height / 2);
		if (wall_top_pixel < 0)
			wall_top_pixel = 0;
		wall_bottom_pixel = (S_HEIGHT / 2) + (data->wall_projected_height / 2);
		if (wall_bottom_pixel > S_HEIGHT)
			wall_bottom_pixel = S_HEIGHT;
		render_image(data, wall_top_pixel, wall_bottom_pixel, i);
		ray_angle += angle_increment;
	}
}

void	put_rays(t_game *data, t_player *player)
{
	double	i;
	double	x;
	double	y;
	double	j;
	double	ray_angle;

	i = 0;
	ray_angle = player->rotation_angle - (player->fov / 2);
	while (i < data->num_rays)
	{
		j = 0;
		while (j < 20)
		{
			x = (player->x * MINIMAP) + cos(ray_angle) * j;
			y = (player->y * MINIMAP) + sin(ray_angle) * j;
			my_mlx_pixel_put(data, x, y, LIGHT_RED);
			j++;
		}
		ray_angle += player->fov / data->num_rays;
		i++;
	}
}
