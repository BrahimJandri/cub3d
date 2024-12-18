/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reddamss <reddamss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:44:37 by reddamss          #+#    #+#             */
/*   Updated: 2024/11/12 12:56:16 by reddamss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	exit_mssg(char *str)
{
	ft_putstr("Error:\n");//
	ft_putstr(str);
	exit(1);
}

void    build_square(t_game *data, int x, int y, int color)
{

    for(int i = 0;i < 40; i++)
    {
        for(int j = 0; j < 40; j++)
        {
            mlx_pixel_put(data->mlx_ptr, data->win_ptr, x + i, y + j, color);
            // usleep(10);
        }
    }

}

void       build_player(t_game *data, int x, int y, int color)
{

    for(int i = 0;i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            mlx_pixel_put(data->mlx_ptr, data->win_ptr, x + i, y + j, color);
            // usleep(10);
        }
    }

}

int    check_number(char c)
{
    if(c == '1')
        return GOLDEN;
    if(c == '0')
        return CREAM;
    return GREY;
}
