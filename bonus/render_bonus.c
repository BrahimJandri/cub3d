/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:04:23 by reddamss          #+#    #+#             */
/*   Updated: 2025/02/08 19:15:32 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Headers/cub3d_bonus.h"

void	draw_map(t_game *data)
{
	data->img->img = mlx_new_image(data->mlx, S_WIDTH, S_HEIGHT);
	if (!data->img->img)
		free_hepler(data, 2);
	data->img->addrs = mlx_get_data_addr(data->img->img, &data->img->bpp,
			&data->img->size_line, &data->img->endian);
	if (!data->img->addrs)
		free_hepler(data, 1);
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

void	projection_wall(t_game *data, t_player *player, double ray_angle)
{
	data->corrected_wall = data->ray->distance * cos(ray_angle
			- player->rotation_angle);
	data->distance_projectplan = (S_WIDTH / 2) / tan(player->fov / 2);
	data->wall_projected_height = (TILE / data->corrected_wall)
		* data->distance_projectplan;
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
		projection_wall(data, player, ray_angle);
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
