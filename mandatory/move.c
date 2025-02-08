/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:27:31 by reddamss          #+#    #+#             */
/*   Updated: 2025/02/08 19:12:14 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Headers/cub3d.h"

int	player_control(int key, t_game *data)
{
	t_player	*player;

	player = data->player;
	if (key == UP || key == W)
		player->walk_dir = 1;
	else if (key == DOWN || key == S)
		player->walk_dir = -1;
	else if (key == RIGHT)
		player->turn_dir = 0.02;
	else if (key == LEFT)
		player->turn_dir = -0.02;
	else if (key == A)
		player->side_dir = -1;
	else if (key == D)
		player->side_dir = 1;
	else if (key == ESC)
	{
		escape_free(data);
		free_all(data);
		exit(0);
	}
	return (1);
}

int	key_release(int key, t_game *data)
{
	t_player	*player;

	player = data->player;
	if (key == UP || key == W)
		player->walk_dir = 0;
	else if (key == DOWN || key == S)
		player->walk_dir = 0;
	else if (key == RIGHT)
		player->turn_dir = 0;
	else if (key == LEFT)
		player->turn_dir = 0;
	else if (key == A)
		player->side_dir = 0;
	else if (key == D)
		player->side_dir = 0;
	return (1);
}

void	update_sides(t_game *data, t_player *player)
{
	double	new_posx;
	double	new_posy;
	int		new_x;
	int		new_y;

	new_posx = player->x + cos(player->rotation_angle + (PI / 2))
		* player->side_dir * player->move_speed;
	new_posy = player->y + sin(player->rotation_angle + (PI / 2))
		* player->side_dir * player->move_speed;
	new_x = (int)(new_posx / TILE);
	new_y = (int)(new_posy / TILE);
	if (data->map[new_y][new_x] == '0')
	{
		player->x = new_posx;
		player->y = new_posy;
	}
}

void	update_player(t_game *data, t_player *player)
{
	double	new_posx;
	double	new_posy;
	int		new_x;
	int		new_y;

	new_posx = player->x + cos(player->rotation_angle) * player->walk_dir
		* player->move_speed;
	new_posy = player->y + sin(player->rotation_angle) * player->walk_dir
		* player->move_speed;
	new_x = (int)(new_posx / TILE);
	new_y = (int)(new_posy / TILE);
	if (data->map[new_y][new_x] == '0')
	{
		player->x = new_posx;
		player->y = new_posy;
	}
}
