#ifndef CUBE_H
#define CUBE_H


#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1
#endif

#include <stdio.h>
#include <unistd.h>
#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include <math.h>
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

#define S_WIDTH 1200
#define S_HEIGHT 800

#define TILE 40
#define PI 3.14159265358979323846
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

typedef struct s_game
{
    void    *mlx;
    void    *win;
    void    *img;
    char    **map;
    int     map_y;
    int     map_x;
    t_player    *player;
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
void    draw_line(t_player *player, t_game *data);
int     player_control(int key, t_game *data);
void    update_player(t_game *data, t_player *player);


void    update_rotation(t_game *data, t_player *player);
#endif