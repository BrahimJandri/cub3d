/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 23:40:54 by rachid            #+#    #+#             */
/*   Updated: 2025/02/08 18:51:59 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Headers/cub3d.h"

void	horizontal_intercepts(t_game *data, t_player *player, t_ray *ray,
		double angle)
{
	double	y_intercept;
	double	x_intercept;

	y_intercept = floor(player->y / TILE) * TILE;
	if (ray->ray_down)
		y_intercept += TILE;
	x_intercept = player->x + (y_intercept - player->y) / tan(angle);
	horizontal_steps(x_intercept, y_intercept, data, angle);
}

void	horizontal_steps(double x_next_touch, double y_next_touch, t_game *data,
		double angle)
{
	double	x_steps;
	double	y_steps;
	double	step_touch[4];
	t_ray	*ray;

	ray = data->ray;
	y_steps = TILE;
	if (ray->ray_up)
		y_steps *= -1;
	x_steps = TILE / tan(angle);
	if (ray->ray_left && x_steps > 0)
		x_steps *= -1;
	if (ray->ray_right && x_steps < 0)
		x_steps *= -1;
	if (ray->ray_up)
		y_next_touch--;
	step_touch[0] = x_next_touch;
	step_touch[1] = y_next_touch;
	step_touch[2] = x_steps;
	step_touch[3] = y_steps;
	get_horizontal_hit(data, step_touch, ray);
}

void	vertical_intercepts(t_game *data, t_player *player, t_ray *ray,
		double angle)
{
	double	y_intercept;
	double	x_intercept;

	x_intercept = floor(player->x / TILE) * TILE;
	if (ray->ray_right)
		x_intercept += TILE;
	y_intercept = player->y + ((x_intercept - player->x) * tan(angle));
	vertical_steps(x_intercept, y_intercept, data, angle);
}

void	vertical_steps(double x_next_touch, double y_next_touch, t_game *data,
		double angle)
{
	double	x_steps;
	double	y_steps;
	double	step_touch[4];
	t_ray	*ray;

	ray = data->ray;
	x_steps = TILE;
	if (ray->ray_left)
		x_steps *= -1;
	y_steps = TILE * tan(angle);
	if (ray->ray_up && y_steps > 0)
		y_steps *= -1;
	if (ray->ray_down && y_steps < 0)
		y_steps *= -1;
	if (ray->ray_left)
		x_next_touch--;
	step_touch[0] = x_next_touch;
	step_touch[1] = y_next_touch;
	step_touch[2] = x_steps;
	step_touch[3] = y_steps;
	get_vertical_hit(data, step_touch, ray);
}
