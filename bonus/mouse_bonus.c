/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachid <rachid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 09:52:42 by rachid            #+#    #+#             */
/*   Updated: 2025/02/08 09:14:03 by rachid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Headers/cub3d_bonus.h"

int	click_press(int key, int x, int y, t_game *data)
{
	t_player	*player;

	player = data->player;
	(void)x;
	(void)y;
	if (key == 1)
	{
		player->turn_dir = -0.02;
	}
	else if (key == 3)
	{
		player->turn_dir = 0.02;
	}
	return (0);
}

int	click_release(int key, int x, int y, t_game *data)
{
	t_player	*player;

	player = data->player;
	(void)x;
	(void)y;
	if (key == 1)
	{
		player->turn_dir = 0;
	}
	else if (key == 3)
	{
		player->turn_dir = 0;
	}
	return (0);
}
