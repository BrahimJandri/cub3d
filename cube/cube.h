/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reddamss <reddamss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:51:31 by reddamss          #+#    #+#             */
/*   Updated: 2024/11/14 11:03:49 by reddamss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
#define CUBE_H

#include <stdio.h>
#include <unistd.h>
#include "minilibx-linux/mlx.h"
#include "libft/libft.h"
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1
#endif



#define PI 3.141592653
#define TWO_PI 6.283185307

# define UP 65362
# define DOWN 65364
# define RIGHT 65363
# define LEFT 65361
# define A 97
# define W 119
# define S 115
# define D 100 
#define ESC 65307
#define Q 113


/****** COLORS *****/
#define GREY 0x808080
#define RED 0xFF0000
#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define GOLDEN 0xFFDF00
#define CREAM 0xFFFDD0

//----------------------//

#define S_W 40
#define S_H 40
#define ROT_SPEED 0.045
#define SQUARE_SIZE 10
#define FOV 60
#define TILE_SIZE 20
#define PLYER_SPEED 4


typedef struct s_player
{
    int   x; //the x position of the player it should be window width /2 so it can be centered
    int   y; //the y position of the player it should be window width /2 so it can be centered
    float   width; //width of the player
    float   height; // height of the player
    int     turn_direction;
    int     walk_direction;
    float   rotaion; //the rotation angle should be PI / 2
    int     walk_speed;//basically the speed of moving;
    int     turn_speed;// speed of turning should be (NUMER) * (PI / 180)idk y
}t_player;


typedef struct s_game
{
    void    *mlx_ptr;
    void    *win_ptr;
    void    *img_ptr;
    char    **map;
    int     map_y;//width units of the map
    int     map_x;//height units of the map
    int     x;
    int     y;
    t_player *user;
}t_game;

void    create_player(t_game *data);
void    draw_line(void  *mlx, void *win, int x_start, int y, int len);
void    init_player(t_player *player);
int    move_player(int keycode, t_game *data);



void    build_square(t_game *data, int pos_x, int pos_y, int color);
void    build_player(t_game *data, int x, int y, int color);
int    check_number(char c);

//****************Functions that were taken from so_long********************//
void	exit_mssg(char *str);
void	read_map(char *av, t_game *data);
void	allocate_map(char *av, t_game *data);
void	draw_map(t_game *data);

//**************** Get_next_line functions ********************//
char	*get_strjoin(char *s1, char *s2);
char	*remaining(char *blended);
char	*extract(char *blended);
char	*fill(int fd, char *pail);
char	*get_next_line(int fd);

#endif