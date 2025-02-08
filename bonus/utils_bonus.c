/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 00:01:02 by rachid            #+#    #+#             */
/*   Updated: 2025/02/08 18:51:11 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Headers/cub3d_bonus.h"

double	cal_len(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}

double	normalize_angle(double angle)
{
	angle = fmod(angle, TWO_PI);
	if (angle < 0)
	{
		angle = angle + TWO_PI;
	}
	return (angle);
}

int	is_it_wall(t_game *data, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (x / TILE);
	map_y = (y / TILE);
	if ((x < 0 || x > data->map_width * TILE) || (y < 0 || y > data->map_height
			* TILE))
	{
		return (1);
	}
	if (data->map[map_y][map_x] != '0')
		return (1);
	return (0);
}

void	error_msg(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}
