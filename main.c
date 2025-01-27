/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachid <rachid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:09:58 by reddamss          #+#    #+#             */
/*   Updated: 2025/01/27 13:38:58 by rachid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Headers/cub3d.h"
//x -> -- horizontal , y = | vertical

int get_plyr_pos(t_game *data)
{
    int	x;
	int	y;

	y = 0;
    printf("height of map%d\n", data->map_height);
	while (y < data->map_height)//is small than the height
	{
		x = 0;
		while (x < data->map_width)//is small than the width
		{
            if(ft_strchr("NSEW", data->map[y][x]))
            {
                data->player->character = data->map[y][x];
                data->player->x = x * TILE + (TILE/2);
                data->player->y = y * TILE + (TILE/2);
                data->map[y][x] = '0';
            }
			x++;
		}
		y++;
	}
    return(-1);
}


void    set_direction(t_game *data)
{
    if(data->player->character == 'N')
        data->player->rotationAngle = ((PI * 3) / 2);
    else if(data->player->character == 'S')
        data->player->rotationAngle = (PI / 2);
    else if(data->player->character == 'E')
        data->player->rotationAngle = 0;
    else if(data->player->character == 'W')
        data->player->rotationAngle = PI;
}


void    init_player(t_game *data)
{
    t_player *dot;

    dot = malloc(sizeof(t_player ));
    dot->radius = TILE / 5;
    dot->turnDir = 0;
    dot->walkDir = 0;
    dot->sideDir = 0;
    dot->moveSpeed = 20;
    dot->rotationSpeed = 2 * (PI / 2);
    dot->line_lenght = 50;
    dot->angle = 0;


    data->player = dot;
    data->num_rays = S_WIDTH / WALL_WIDTH ;

    
    
}


void    init_ray(t_game *data)
{
    t_ray *raay = malloc(sizeof(t_ray) * data->num_rays);
    if(!raay)
        return ;
    data->ray = raay;

    get_plyr_pos(data);
    set_direction(data);



}


//array: 0 = so, 1 = no, 2 = we, 3 = ea;
t_texture *upload_texture(t_game *data, int i)
{
    t_texture *tex;

    tex = malloc(sizeof(t_texture));
    if(!tex)
        return NULL;
    if(i == 0)
        tex->img = mlx_xpm_file_to_image(data->mlx, data->so_texture, &tex->tex_width, &tex->tex_height);
    else if(i == 1)
        tex->img = mlx_xpm_file_to_image(data->mlx, data->no_texture, &tex->tex_width, &tex->tex_height);
    else if(i == 2)
        tex->img = mlx_xpm_file_to_image(data->mlx, data->we_texture, &tex->tex_width, &tex->tex_height);
    else if(i == 3)
        tex->img = mlx_xpm_file_to_image(data->mlx, data->ea_texture, &tex->tex_width, &tex->tex_height);
    if(!tex->img)
        error_msg("mlx_xpm_file_to_image Failed");

    tex->addrs = mlx_get_data_addr(tex->img, &tex->bpp, &tex->size_line, &tex->endian);
    if(!tex->addrs)
        error_msg("Failed to get address of the image");
    return(tex);
}


//array: 0 = so, 1 = no, 2 = we, 3 = ea;
void    get_textures(t_game *data)
{
    int i;

    i = 0;
    while(i < 4)
    {
        data->texture[i] = upload_texture(data, i);
        i++;
    }
    return ;
}


int main(int ac, char **av)
{
  	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
    if(!game)
    {
        return 1;
    }
        
	if(ac != 2)
    {
		return (ft_putstr_fd("Error\nUsage : Cub3d map.cub\n", 2), free(game),1);
    }
    // t_image image;
    (void)ac;
    
    init_player(game);//init dakchi d lplayer kamlo hna
    parse_config(game, av);
    init_ray(game);
    
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, S_WIDTH, S_HEIGHT, "gta");

    get_textures(game);
  
 
    game->img = malloc(sizeof(t_image));
    if(!game->img)
        return 1;
        
    mlx_loop_hook(game->mlx, (void *)game_loop, game);//rsm lmap o zid lplayer o fov flkher d lfunction
    // mlx_loop_hook()
    mlx_hook(game->win, 2, (1L << 0), player_control, game);
    mlx_hook(game->win, 3, (1L << 1), key_release, game);
    mlx_loop(game->mlx);
    free_all(game);
}
    // (void)ac;
    // (void)av;o ft_memchr.o ft_itoa.o ft_isprint.o ft_isdigit.o ft_striteri.o ft_putL