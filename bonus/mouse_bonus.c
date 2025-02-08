/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 09:52:42 by rachid            #+#    #+#             */
/*   Updated: 2025/02/08 18:47:55 by bjandri          ###   ########.fr       */
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

void	free_hepler(t_game *data, int c)
{
	if (c == 1)
	{
		mlx_destroy_image(data->mlx, data->img->img);
		escape_free(data);
		free_all(data);
		error_msg("Img failed\n");
	}
	else
	{
		mlx_destroy_image(data->mlx, data->img->img);
		free_parse(data);
		free(data->minimap);
		destroy_sprite(data);
		escape_free(data);
		free(data);
		error_msg("Img failed\n");
	}
}
