/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reddamss <reddamss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 00:01:02 by rachid            #+#    #+#             */
/*   Updated: 2025/02/04 10:28:06 by reddamss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Headers/cub3d_bonus.h"


int    check_number(char c)
{
    if(c == '1')
        return GREY;
    if(c == '0' || c == 'N')
        return WHITE;
    return GOLDEN;
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
    int map_x;
    int map_y;
    int index;
    
    map_x = (x / TILE);
    map_y = (y / TILE);
    if((x < 0 || x > data->map_width * TILE) || (y < 0 || y > data->map_height * TILE))
    {
        return 1;
    }

    printf("mapy = %d. mapx = %d\n", map_y, map_x);
    if(data->map[map_y][map_x] == 'D')
    {
        index = get_index(data, map_y, map_x);
        if(index == -1)
            exit(17);
        if(!data->door[index].open)
            return (1);
        if(data->flag && data->door[index].open)
            return (1);  
    }
    else if(data->map[map_y ][map_x] != '0')
        return 1;
    return 0;
}

void	error_msg(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}
