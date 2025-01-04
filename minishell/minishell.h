#ifndef CUBE_H
#define CUBE_H


#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1
#endif

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include "../minilibx-linux/mlx.h"
#include "../minilibx-linux/mlx_int.h"
#include "../libft/libft.h"
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <fcntl.h>

/*----------- CONTROL KEYS ----------*/
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




/*----------- COLORS ----------*/
#define GREY 0x808080
#define RED 0xFF0000
#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define GOLDEN 0xFFDF00
#define CREAM 0xFFFDD0

#define S_WIDTH 1350
#define S_HEIGHT 700
#define WALL_WIDTH 1
#define MINIMAP 0.2


#define TILE 20
#define PI 3.14159265358979323846
#define TWO_PI 6.28318530718 
#define FOV 60 * (PI / 180)


/*_______________IMAGES_STRUCT_________________*/
typedef struct s_image
{
    void    *img;

}t_image;


/*_______________PLAYER_STRCUT_________________*/
typedef struct s_player
{
    double      x;
    double      y;
    int      radius;
    double      turnDir;
    double      walkDir;
    double      rotationAngle;
    double      rotationSpeed;
    double      moveSpeed;
    double      fov;
    double      angle;
    double      line_lenght;
} t_player;

/*________________RAY_STRUCT_________________*/
typedef struct s_ray
{
    //used double data type for NOW, u can change it later;
    double      x_hit;
    double      y_hit;
    double      distance;
    bool        ray_down;
    bool        ray_up;
    bool        ray_right;
    bool        ray_left;
    double      x_steps;
    double      y_steps;
    double      x_intercept;
    double      y_intercept;
}t_ray;

/*________________GAME_STRUCT________________*/
typedef struct s_game
{
    void    *mlx;
    void    *win;

    int     bitppixel;
    int     size_line;
    int     endian;
    char    *addrs;
    void    *img;

    char    **map;
    int     map_y;
    int     map_x;//|||||||||||||||||||||||||||||||||||||||||
    double  num_rays;
    // you were going to add the number of rays the player will have
    t_player    *player;
    t_ray       *ray;
}t_game;


/*______________get_next_line________________*/

char	*get_next_line(int fd);
char	*get_strjoin(char *s1, char *s2);


/*_________________so_long___________________*/

void	read_map(char *av, t_game *data);
void	exit_mssg(char *str);
void	allocate_map(char *av, t_game *data);

/*_____________new_functions______________*/

void    build_square(t_game *data, int x, int y, int color);
int    check_number(char c);
void	draw_map(t_game *data);
void    draw_circle(t_player *player, t_game *data);
void    draw_line(t_player *player, t_game *data, double x_hit, double  y_hit );
int     player_control(int key, t_game *data);
void    update_player(t_game *data, t_player *player);


void    update_rotation(t_game *data, t_player *player);


/*_____________functions_functions______________*/

void    draw_rays(t_player *player, t_game *data);
double      normalize_angle(double angle);
void    cast_rays(t_player *player, t_game *data, double angle);
int     key_release(int key, t_game *data);

void    draw_rectangle(t_game *data, int x, int y, int height, int width);

#endif