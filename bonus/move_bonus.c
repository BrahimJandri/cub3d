/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:27:31 by reddamss          #+#    #+#             */
/*   Updated: 2025/02/08 18:39:52 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Headers/cub3d_bonus.h"

void	destroy_xpm(t_game *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		mlx_destroy_image(data->mlx, data->texture[i]->img);
		i++;
	}
	i = 0;
	while (i < 4)
		free(data->texture[i++]);
	return ;
}

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
	if (key == SPACE)
		player->jab = 1;
	else if (key == ESC)
	{
		destroy_sprite(data);
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
	if (data->map[(int)(player->y / TILE)][new_x] == '0')
		player->x = new_posx;
	if (data->map[new_y][(int)(player->x / TILE)] == '0')
		player->y = new_posy;
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
	if (data->map[(int)(player->y / TILE)][new_x] == '0')
		player->x = new_posx;
	if (data->map[new_y][(int)(player->x / TILE)] == '0')
		player->y = new_posy;
}
