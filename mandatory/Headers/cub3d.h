#ifndef CUBE_H
#define CUBE_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1
#endif

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include "../../library/minilibx/mlx.h"
#include "../../library/Libft/libft.h"
#include "../../library/get_next_line/get_next_line.h"
#include <math.h>
#include <limits.h>
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
#define BLUE_SKY 0x019CE0
#define EARTH_COLOR 0xB07C57
#define RED 0xFF0000
#define LIGHT_RED 0xFF4F4B
#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define GOLDEN 0xFFDF00
#define CREAM 0xFFFDD0

#define S_WIDTH 700
#define S_HEIGHT 640
#define WALL_WIDTH 1
#define MINIMAP 0.2

// #define TEX
#define TILE 256
// #define TEX_WIDTH
// #define TEX_HEIGHT 400
#define PI 3.14159265358979323846
#define TWO_PI 6.28318530718
#define FOV 60 * (PI / 180)

/*_______________IMAGES_STRUCT_________________*/
typedef struct s_image
{
    int bpp;
    int size_line;
    int endian;
    char *addrs;
    void *img;
} t_image;

typedef struct s_texture
{
    int bpp;
    int size_line;
    int endian;
    char *addrs;
    void *img;
    int tex_width;
    int tex_height;
    void *tex_data;
} t_texture;

/*_______________PLAYER_STRCUT_________________*/
typedef struct s_player
{
    double x;
    double y;
    int radius;
    double turnDir;
    double walkDir;
    double sideDir;
    double rotationAngle;
    double rotationSpeed;
    double moveSpeed;
    double fov;
    double angle;
    double line_lenght;
    char character;
} t_player;

/*________________RAY_STRUCT_________________*/
typedef struct s_ray
{
    // used double data type for NOW, u can change it later;
    double h_hitx;
    double h_hity;
    double v_hitx;
    double v_hity;
    double distance;
    bool ray_down;
    bool ray_up;
    bool ray_right;
    bool ray_left;
    bool found_h_wall;
    bool found_v_wall;
    bool is_vert;
    double x_wall;
    double y_wall;
} t_ray;

/*_______________
_GAME_STRUCT________________*/
typedef struct s_game
{
    void *mlx;
    void *win;

    char **map;
    char **map_dup;
    int floor_color;
    int ceiling_color;
    int config_count;

    char *no_texture;
    char *we_texture;
    char *so_texture;
    char *ea_texture;

    int map_height;
    int map_width;

    double num_rays;

    void *wall_tex;
    int tex_width;
    int tex_height;
    unsigned int *tex_data;

    double corrected_wall;
    double distance_projectplan;
    double wall_projected_height;

    unsigned int color;

    // you were going to add the number of rays the player will have
    t_player *player;
    t_ray *ray;
    t_image *img;
    t_texture *texture[4];
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

int is_it_wall(t_game *data, double x, double y);
void define_angle(t_ray *ray, double angle);

void draw_minimap(t_game *data);

int shade_walls(int color, double distance);
int apply_shadow(int color, double shadow_factor);

void put_rays(t_game *data, t_player *player);

void update_sides(t_game *data, t_player *player);
void get_data(t_game *data);
void game_loop(t_game *data);

/*__________RAYCASTING_________*/
void horizontal_intercepts(t_game *data, t_player *player, t_ray *ray, double angle);
void horizontal_steps(double x_next_touch, double y_next_touch, t_game *data, double angle);
void vertical_intercepts(t_game *data, t_player *player, t_ray *ray, double angle);
void vertical_steps(double x_next_touch, double y_next_touch, t_game *data, double angle);
void get_vertical_hit(t_game *data, double array[4], t_ray *ray);
void get_horizontal_hit(t_game *data, double array[4], t_ray *ray);
void closer_intersection(t_player *player, t_ray *ray);
double calcul_line_length(double x1, double y1, double x2, double y2);

t_texture *upload_texture(t_game *data, int i);

void destroy_xpm(t_game *data);

/*______BRAHIM___________*/
void error_msg(char *str);
void parse_config(t_game *game, char **av);
void read_map(t_game *game, char *file);
void draw_map(t_game *game);
void check_extension(const char *file, t_game *game);
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
char *skip_empty_lines(int fd, t_game *game);
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
void validate_and_parse_color_values(char **parts, int *colors, t_game *game);
void validate_color_format(char *str);
void check_texture_validtion(t_game *game);
void second_free(t_game *game, char *str);
void first_free(t_game *game, char *str);
#endif