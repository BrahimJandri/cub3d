/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:27:31 by reddamss          #+#    #+#             */
/*   Updated: 2025/02/08 16:19:50 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./Headers/cub3d.h"


void    destroy_xpm(t_game *data)
{
    int i;

    i = 0;
    while(i < 4)
    {
        mlx_destroy_image(data->mlx, data->texture[i]->img);
        i++;
    }
    i = 0;
    while(i < 4)
        free(data->texture[i++]);
    return ;
}


void    free_parse(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i])
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
	game->map = NULL;
	free_texture(game);
    // free(game->minimap);// commented for sprites
}

void    wall_tex_free(t_game *data)
{
    free(data->ray);
    mlx_destroy_window(data->mlx, data->win);
    mlx_destroy_display(data->mlx);
    free(data->mlx);
    free(data->player);
    // free(data->img);
    free(data->gun);
    free_parse(data);
    free(data);
}


void    escape_free(t_game *data)
{
    // destroy_path(data); //deleted for ESC and CROSS
    free(data->ray);
    destroy_xpm(data);
    mlx_destroy_window(data->mlx, data->win);
    mlx_destroy_display(data->mlx);
    free(data->mlx);
    free(data->player);
    free(data->img);
}

int     player_control(int key, t_game *data)
{
    t_player *player;

    player = data->player;
    if (key == UP || key == W)
        player->walk_dir = 1;
    else if (key == DOWN || key == S)
        player->walk_dir= -1;
    else if (key == RIGHT)
        player->turn_dir = 0.02;
    else if (key == LEFT)
        player->turn_dir = -0.02;
    else if (key == A)
        player->side_dir = -1;
    else if(key == D)
        player->side_dir = 1;
    else if(key == ESC)
    {
        escape_free(data);
        free_all(data);
        exit(0);
    }
    return 1;
}


int     key_release(int key, t_game *data)
{
        t_player *player;

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
    else if(key == D)
        player->side_dir = 0;
    return 1;
}
void update_sides(t_game *data, t_player *player)
{
    double new_posx, new_posy;
    int new_x, new_y;

    new_posx = player->x + cos(player->rotationAngle + (PI / 2)) * player->side_dir * player->moveSpeed;
    new_posy = player->y + sin(player->rotationAngle + (PI / 2)) * player->side_dir * player->moveSpeed;

    new_x = (int)(new_posx / TILE);
    new_y = (int)(new_posy / TILE);

    if (data->map[new_y][new_x] == '0')  
    {
        player->x = new_posx;
        player->y = new_posy;
    }

}

void update_player(t_game *data, t_player *player)
{
    double new_posx, new_posy;
    int new_x, new_y;

    new_posx = player->x + cos(player->rotationAngle) * player->walk_dir * player->moveSpeed;
    new_posy = player->y + sin(player->rotationAngle) * player->walk_dir * player->moveSpeed;

    new_x = (int)(new_posx / TILE);
    new_y = (int)(new_posy / TILE);

    if (data->map[new_y][new_x] == '0')  
    {
        player->x = new_posx;
        player->y = new_posy;
    }

}



