/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachid <rachid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 00:01:02 by rachid            #+#    #+#             */
/*   Updated: 2025/01/19 00:05:33 by rachid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Headers/cub3d_bonus.h"


int check_number(char c)
{
    if (c == '1')
        return GREY;    // Wall
    if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
        return WHITE;   // Floor
    return GOLDEN;      // Default color
}

double      calcul_line_length(double   x1, double y1, double x2, double y2)
{
    return(sqrt(pow(x1 - x2,2) + pow(y1 - y2, 2)));
}

double      normalize_angle(double angle)
{
    angle = fmod(angle, TWO_PI);
    if(angle < 0)
    {
        angle = angle + TWO_PI;
    }
    return angle;
}

int    is_it_wall(t_game *data, double   x, double   y)
{
    if((x < 0 || x > data->map_width * TILE) || (y < 0 || y > data->map_height * TILE))
    {
        return 1;
    }
    double map_x;
    double map_y;

    map_x = floor(x / TILE);
    map_y = floor(y / TILE);
    return(data->map[(int)map_y ][(int)map_x] != '0');
}

void	error_msg(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}
