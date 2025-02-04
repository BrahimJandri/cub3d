/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reddamss <reddamss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:09:58 by reddamss          #+#    #+#             */
/*   Updated: 2025/02/04 11:45:32 by reddamss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Headers/cub3d_bonus.h"
//x -> -- horizontal , y = | vertical

int get_plyr_pos(t_game *data)
{
    int	x;
	int	y;

	y = 0;
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
    dot->moveSpeed = 8;
    dot->rotationSpeed = 1 * (PI / 2);
    dot->line_lenght = 50;
    dot->angle = 0;
    dot->frames = 0;
    dot->bullets = 0;



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

int     close_window(t_game *data)
{
    free(data->ray);
    destroy_xpm(data);
    mlx_destroy_window(data->mlx, data->win);
    mlx_destroy_display(data->mlx);
    free(data->mlx);
    free(data->player);
    free(data->img);
    free_all(data);
    exit(0);
}

void circle(t_game *data, int x, int y, int radius)
{
    int i, j;

    for (i = x - radius; i <= x + radius; i++)    // mini_map(data);
    // draw_circle(data->player, data);
    {
        for (j = y - radius; j <= y + radius; j++)
        {
            if ((i - x) * (i - x) + (j - y) * (j - y) <= radius * radius)
                mlx_pixel_put(data->mlx, data->win, i, j, 0xFFFFFF); // White circle
        }
    }
}
//1 = right, 3 = left
int     click_press(int key, int x, int y, t_game *data)
{
    t_player *player;
    // mini_map(data);
    // draw_circle(data->player, data);
    player = data->player;
    (void)x;
    (void)y;
    if(key == 1)
    {
        player->turnDir = -0.02;
    }
    else if(key == 3)
    {
        player->turnDir = 0.02;
    }
    return 0;
}

int     click_release(int key, int x, int y, t_game *data)
{
    t_player *player;

    player = data->player;
    (void)x;
    (void)y;
    if(key == 1)
    {
        player->turnDir = 0;
    }    // mini_map(data);
    // draw_circle(data->player, data);
    else if(key == 3)
    {
        player->turnDir = 0;
    }
    return 0;
}

//000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
//000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
//000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
//000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
//000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
//____________________________________________________BONUS_____________________________________________________//

void    load_gun_frames(t_game *data)
{
    int i;

    i = 0;
    while(i < FRAMES)
    {
        data->gun[i].img = mlx_xpm_file_to_image(data->mlx, data->gun[i].path, &data->gun[i].tex_width, &data->gun[i].tex_height);
        if(!data->gun[i].img)
        {
            //free
            printf("oho\n");
            exit(1);
        }
        data->gun[i].addrs = mlx_get_data_addr(data->gun[i].img, &data->gun[i].bpp, &data->gun[i].size_line, &data->gun[i].endian);
        if(!data->gun[i].addrs)
        {
            printf("lhamdullah\n");
            exit(1);
        }
        i++;
    }
}

void    render_gun(t_game *data)
{
    if (data->player->bullets)
	{
		data->player->frames++;
        // usleep(100000);
		if (data->player->frames >= FRAMES)
		{
			data->player->frames = 0;
			data->player->bullets = 0;
		}
        // printf("frames = %d\n", data->player->frames);
        put_gun(data, data->player->frames);
	}
	if (!data->player->bullets && data->player->frames != 0)
	{
		data->player->frames--;
	}
}

void    put_gun(t_game *data, int frame)
{
    double  x;
    double  y;
    int i;
    int j;
    int color;
    
    i = 0;
    x = (S_WIDTH - data->gun[frame].tex_width)/2;
    y = (S_HEIGHT - data->gun[frame].tex_height);
    // x = (S_WIDTH / 2);
    // y = (S_HEIGHT / 2);
    
    while(i < data->gun[frame].tex_height)
    {
        j = 0;
        while(j < data->gun[frame].tex_width)
        {
    		color = *(unsigned int *)(data->gun[frame].addrs + (i * data->gun[frame].size_line + j * (data->gun[frame].bpp / 8)));
			if ((unsigned int)color != 0xFF000000)
            {
                // printf("x + j= %f y + i = %f\n",x + j, y+i);
				my_mlx_pixel_put(data, j + x, i + y, color);
                // printf("HERE\n");    
            }
			j++;
        }
        i++;
    }
}

void    init_sprites(t_game *data)
{
    int i;
    char *number;
    t_texture *gun;

    gun = malloc(sizeof(t_texture) * FRAMES);
    
    i = 0;
    while(i < FRAMES)
    {
        gun[i].path = ft_strdup("./Textures/braha/");
        number = ft_itoa(i);
        gun[i].path = ft_strjjoin(gun[i].path, number);
        gun[i].path = ft_strjjoin(gun[i].path, ".xpm");
        free(number);
        i++;
    }
    data->gun = gun;
}

//000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
//000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
//000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
//000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000



//000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
//000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
//000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
//000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

void    ft_player_wall_hit(t_game *data)
{
    int x;
    int y;
    int index;

    cast_rays(data->player, data, data->player->rotationAngle);
    x = (int)(data->ray->x_wall / TILE);
    y = (int)(data->ray->y_wall / TILE);
    // printf("distance = %f\n", data->ray->distance);
    if(x >= 0 && x < data->map_width && y >= 0 && y < data->map_height)
    {
        if(data->map[y][x] == 'D' && data->ray->distance < DOOR_DISTANCE)
        {
            // printf("YAAAAAAAAAAAAAAAY\n");
            index = get_index(data, y, x);
            if(index == -1)
                exit(12);
            if(data->door[index].open)
                data->door[index].open = false;
            else if (!data->door[index].open)
                data->door[index].open = true;
            
        }
    }
    //___I CALL CAST RAYS TO GET ME THE INFOS OF THE INTER SECTION BUT I NEED TO KNOW THE ANGLE OF THE RAY.
    //___THE ANGLE WILL BE KNOW BY USING THE NORMALIZE_ANGLE FUNCTION__
    //___BUT THIS MEANS YOU WILL USE ONLY ONE RAY TO GET THE DOOR POSITION


    
    //gets the position of the wall hit and checks if this wall is a door or not
    //after it gets the index of that door and opens it if it's closed and close it if it's open
}
// -->in update data when player wants to move
/*_the place where you update the next move of the player. you check if it is a white space or not 
    in this function you need to check if it is a wall too
    -- now we can move inside the door if it is open, and can't if it is the oposite
     _*/

int     get_index(t_game *data, int y, int x)
{
    int index;

    index = 0;
    while(index < data->door_num)
    {
        printf("data->door[%d].x = %d, data->door[%d].y = %d\n", index, data->door[index].x, index, data->door[index].y);
        if(data->door[index].x == x && data->door[index].y == y)
            return index;
        index++;
    }
    printf("_________________________________________________\n");
    return (-1);
}
// will find it in render file, get_data function
int     x_accessibility(t_game *data, int y, double new_x)
{
    int index;

    // printf("y == %d, x = %d\n", y, (int)(new_x / TILE));
    index = get_index(data, y, (new_x / TILE));
    if(index == -1)
        exit(11);
    printf("accessible %d\n", data->door[index].open);
    if(data->door[index].open)
        return 1;
    else
        return 0;
}
// will find it in render file, get_data function
int     y_accessibility(t_game *data, int x, double new_y)
{
    int index;

    //gets the index of the tile
    index = get_index(data, new_y / TILE, x);
    if(index == -1)
        exit(13);
    if(data->door[index].open)
        return 1;
    else
        return 0;
}

int    y_side_accessibility(t_game *data, double y, double x)
{
    int index;
    
    (void)x;

    printf("(14) y == %d, x = %d\n", (int)(y / TILE), (int)(data->player->x / TILE));
    index = get_index(data, (int)(y / TILE), (int)(data->player->x / TILE));
    
    if(index == -1)
        exit(14);
    if(data->door[index].open)
        return 1;
    else
        return 0;
}

int    x_side_accessibility(t_game *data, double y, double x)
{
    int index;
    
    printf("(15) y == %d, x = %d\n", (int)(y / TILE), (int)(x / TILE));
    index = get_index(data, (int)(y / TILE), (int)(x / TILE));
    if(index == -1)
        exit(15);
    if(data->door[index].open)
        return 1;
    else
        return 0;
}

int    get_doors_num(t_game *data)
{
    int door;
    int i;
    int j;

    i = 0;
    door = 0;
    while(i < data->map_height)
    {
        j = 0;
        while(j < data->map_width)
        {
            if(data->map[i][j] == 'D')
                door++;
            j++;
        }
        i++;
    }
    return (door);
}



void    alloc_doors(t_game * data)
{
    t_door *door;
    //getting the number of the doors
    data->door_num = get_doors_num(data); 
    if(data->door_num)
    {
        door = malloc(sizeof(t_door) * data->door_num);
        if(!door)
        {
            //error message 
            exit(16);
        }
    }
    data->door = door;
}

void    assign_index(t_game *data, int index, int y, int x)
{
    data->door[index].x = x;
    data->door[index].y = y;
    data->door[index].open = false;
}    

void    init_door(t_game *data)
{
    int index;
    int i;
    int j;
    
    i = 0;
    index = 0;
    while(i < data->map_height)
    {
        j = 0;
        while(j < data->map_width)
        {
            if(data->map[i][j] == 'D')
            {
                assign_index(data, index, i, j);
                index++;
            }
            j++;
        }
        i++;
    }
}


//000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
//000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
//000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
//000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000




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
    (void)ac;
    init_player(game);//init dakchi d lplayer kamlo hna
    parse_config(game, av);
    init_ray(game);
    init_sprites(game);
    
    alloc_doors(game);
    init_door(game);
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, S_WIDTH, S_HEIGHT, "gta");

    printf("%s\n", game->gun[0].path);
    get_textures(game);
    game->img = malloc(sizeof(t_image));
    if(!game->img)
        return 1;
    load_gun_frames(game);
    mlx_loop_hook(game->mlx, (void *)game_loop, game);//rsm lmap o zid lplayer o fov flkher d lfunction
    mlx_hook(game->win, 2, (1L<<0), player_control, game);
    mlx_hook(game->win, 3, (1L<<1), key_release, game);
    mlx_hook(game->win, 17, 0, close_window, game);
    mlx_hook(game->win, 4, (1L<<2), click_press, game);
    mlx_hook(game->win, 5, (1L<<3), click_release, game);
    mlx_loop(game->mlx);
}
