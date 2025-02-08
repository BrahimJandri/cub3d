/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 23:40:13 by rachid            #+#    #+#             */
/*   Updated: 2025/02/08 19:00:22 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Headers/cub3d.h"

void	cast_rays(t_player *player, t_game *data, double angle)
{
	t_ray	*ray;

	ray = data->ray;
	ray->found_h_wall = false;
	ray->found_v_wall = false;
	define_angle(ray, angle);
	horizontal_intercepts(data, player, ray, angle);
	vertical_intercepts(data, player, ray, angle);
	closer_intersection(player, ray);
}

void	define_angle(t_ray *ray, double angle)
{
	angle = normalize_angle(angle);
	ray->ray_down = angle > 0 && angle < PI;
	ray->ray_up = !ray->ray_down;
	ray->ray_right = angle < (PI * 0.5) || angle > (1.5 * PI);
	ray->ray_left = !ray->ray_right;
}

void	closer_intersection(t_player *player, t_ray *ray)
{
	double	vhit_dist;
	double	hhit_dist;

	if (ray->found_v_wall)
		vhit_dist = cal_llen(player->x, player->y, ray->v_hitx, ray->v_hity);
	else
		vhit_dist = 9199999999999999999;
	if (ray->found_h_wall)
		hhit_dist = cal_llen(player->x, player->y, ray->h_hitx, ray->h_hity);
	else
		hhit_dist = 9199999999999999999;
	if (hhit_dist < vhit_dist)
	{
		ray->x_wall = ray->h_hitx;
		ray->y_wall = ray->h_hity;
		ray->distance = hhit_dist;
		ray->is_vert = 0;
	}
	else
	{
		ray->x_wall = ray->v_hitx;
		ray->y_wall = ray->v_hity;
		ray->distance = vhit_dist;
		ray->is_vert = 1;
	}
}

/* step_touch[0] = x_next_touch;
 step_touch[1] = y_next_touch;
 step_touch[2] = x_steps;
 step_touch[3] = y_steps; */

void	get_horizontal_hit(t_game *data, double array[4], t_ray *ray)
{
	while (array[1] >= 0 && array[1] <= (data->map_height * TILE)
		&& array[0] >= 0 && array[0] <= (data->map_width * TILE))
	{
		if (is_it_wall(data, array[0], array[1]))
		{
			ray->found_h_wall = true;
			ray->h_hity = array[1];
			ray->h_hitx = array[0];
			break ;
		}
		else
		{
			array[0] += array[2];
			array[1] += array[3];
		}
	}
}

void	get_vertical_hit(t_game *data, double array[4], t_ray *ray)
{
	while (array[1] >= 0 && array[1] <= (data->map_height * TILE)
		&& array[0] >= 0 && array[0] <= (data->map_width * TILE))
	{
		if (is_it_wall(data, array[0], array[1]))
		{
			ray->found_v_wall = true;
			ray->v_hity = array[1];
			ray->v_hitx = array[0];
			break ;
		}
		else
		{
			array[0] += array[2];
			array[1] += array[3];
		}
	}
}
