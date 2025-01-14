#ifndef CUBE_H
#define CUBE_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1
#endif

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include "../library/minilibx/mlx.h"
#include "../library/Libft/libft.h"
#include "../library/get_next_line/get_next_line.h"
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <fcntl.h>

/*----------- CONTROL KEYS ----------*/
#define UP 65362
#define DOWN 65364
#define RIGHT 65363
#define LEFT 65361
#define A 97
#define W 119
#define S 115
#define D 100
#define ESC 65307
#define Q 113

/*----------- COLORS ----------*/
#define GREY 0x808080
#define RED 0xFF0000
#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define GOLDEN 0xFFDF00
#define CREAM 0xFFFDD0

#define S_WIDTH 1900
#define S_HEIGHT 1000
#define WALL_WIDTH 1
#define MINIMAP 0.2

#define TILE 40
#define PI 3.14159265358979323846
#define TWO_PI 6.28318530718
#define FOV 60 * (PI / 180)

/*_______________IMAGES_STRUCT_________________*/
typedef struct s_image
{
    void *img;

} t_image;

/*_______________PLAYER_STRCUT_________________*/
typedef struct s_player
{
    double x;
    double y;
    int radius;
    double turnDir;
    double walkDir;
    double rotationAngle;
    double rotationSpeed;
    double moveSpeed;
    double fov;
    double angle;
    double line_lenght;
} t_player;

/*________________RAY_STRUCT_________________*/
typedef struct s_ray
{
    // used double data type for NOW, u can change it later;
    double x_hit;
    double y_hit;
    double distance;
    bool ray_down;
    bool ray_up;
    bool ray_right;
    bool ray_left;
    double x_steps;
    double y_steps;
    double x_intercept;
    double y_intercept;
} t_ray;

/*________________GAME_STRUCT________________*/
typedef struct s_game
{
    void *mlx;
    void *win;

    int bpp;
    int size_line;
    int endian;
    char *addrs;
    void *img;

    char **map;
    char **map_dup;
    int map_height;
    int map_width; //|||||||||||||||||||||||||||||||||||||||||
    double num_rays;

    char *no_texture;
    char *we_texture;
    char *so_texture;
    char *ea_texture;
    int floor_color;
    int ceiling_color;
    int config_count;

    // you were going to add the number of rays the player will have
    t_player *player;
    t_ray *ray;
} t_game;

/*______________get_next_line________________*/

char *get_next_line(int fd);
char *get_strjoin(char *s1, char *s2);

/*_________________so_long___________________*/

// void read_map(char *av, t_game *data);
void exit_mssg(char *str);
void allocate_map(char *av, t_game *data);

/*_____________new_functions______________*/

void build_square(t_game *data, int x, int y, int color);
int check_number(char c);
void draw_map(t_game *data);
void draw_circle(t_player *player, t_game *data);
void draw_line(t_player *player, t_game *data, double x_hit, double y_hit);
int player_control(int key, t_game *data);
void update_player(t_game *data, t_player *player);

void update_rotation(t_game *data, t_player *player);

/*_____________functions_functions______________*/

void draw_rays(t_player *player, t_game *data);
double normalize_angle(double angle);
void cast_rays(t_player *player, t_game *data, double angle);
int key_release(int key, t_game *data);

void draw_rectangle(t_game *data, int x, int y, int height, int width);
void my_mlx_pixel_put(t_game *data, int x, int y, int color);



/*______BRAHIM___________*/
void error_msg(char *str);
void parse_config(t_game *game, char **av);
void read_map(t_game *game, char *file);
void draw_map(t_game *game);
void check_extension(const char *file);
void count_params(t_game *game);
void check_config(t_game *game);
void check_map_params(t_game *game);
void check_map_boundaries(t_game *game);
void check_first_line(t_game *game, int *j);
void check_last_line(t_game *game, int *j, int *i);
void check_middle_line(t_game *game, int *i, int *j);
void check_map_columns(t_game *game);
void check_column_boundaries(t_game *game, int j);
void check_column_zeros(t_game *game, int j, int i);
void map_dup(t_game *game);
void free_all(t_game *game);
void calculate_map_dimensions(t_game *game, const char *file);
void fill_map(t_game *game, const char *file);
bool ft_flood_fill(int x, int y, t_game *game);
char *skip_empty_lines(int fd);
char *parse_textures_and_colors(t_game *game, char *line, int fd);
char *skip_texture_colors(int fd, char *line);
void parse_texture(char *line, t_game *game, int n);
int parse_color(char *str, t_game *game);
int count_sep(char *str);
int open_file(const char *file);
void free_texture(t_game *game);
void ft_free_split(char **array);
size_t ft_arraylen(char **array);
int ft_isspace(char *str);
void validate_color_parts_count(char **parts);
void validate_and_parse_color_values(char **parts, int *colors);
void validate_color_format(char *str);
void check_texture_validtion(t_game *game);
#endif