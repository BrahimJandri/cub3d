/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachid <rachid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:27:31 by reddamss          #+#    #+#             */
/*   Updated: 2025/02/08 09:11:48 by rachid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./Headers/cub3d_bonus.h"


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

void    destroy_path(t_game *data)
{
    int i;

    i = 0;
    while(i < FRAMES)
    {
        free(data->gun[i].path);
        i++;
    }
    return ;
}

void    destroy_sprite(t_game *data)
{
    int i;

    i = 0;
    while(i < FRAMES)
    {
        mlx_destroy_image(data->mlx, data->gun[i].img);
        i++;
    }
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
    destroy_path(data);
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
    free(data->gun);
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
    else if(key == SPACE)
        player->jab = 1;
    else if(key == ESC)
    {
        destroy_sprite(data);
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

void    update_sides(t_game *data, t_player *player)
{
    double  new_posx;
    double  new_posy;
    int x;
    int y;
    
    new_posx = player->x + cos(player->rotationAngle + (PI / 2)) * player->side_dir * player->moveSpeed;
    new_posy = player->y + sin(player->rotationAngle + (PI / 2)) * player->side_dir * player->moveSpeed;
    
    x = (int)player->x / TILE;
    y = (int)player->y / TILE;
    
    if((data->map[y][(int)new_posx / TILE] == '0'))
        player->x = new_posx;
    if((data->map[(int)new_posy / TILE][x] == '0'))
        player->y = new_posy;
}


void    update_player(t_game *data, t_player *player)
{
    int x;
    int y;
    double new_posx;
    double new_posy;
    
    new_posx = player->x + cos(player->rotationAngle) * player->walk_dir * player->moveSpeed;
    new_posy = player->y + sin(player->rotationAngle) * player->walk_dir * player->moveSpeed;

    x = (int)player->x / TILE;
    y = (int)player->y / TILE;
    if((data->map[y][(int)new_posx / TILE] == '0')) 
        player->x = new_posx;
    if((data->map[(int)new_posy / TILE][x] == '0')) 
        player->y = new_posy;
}


    