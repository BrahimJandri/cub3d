/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:41:13 by bjandri           #+#    #+#             */
/*   Updated: 2025/02/08 18:59:56 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include "../../library/Libft/libft.h"
# include "../../library/get_next_line/get_next_line.h"
# include "../../library/minilibx/mlx.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/*----------- CONTROL KEYS ----------*/
# define UP 65362
# define DOWN 65364
# define RIGHT 65363
# define LEFT 65361
# define A 97
# define W 119
# define S 115
# define D 100
# define Q 113
# define ESC 65307
# define ENTER 65293
# define SPACE 32

/*----------- COLORS ----------*/
# define GREY 0x606060
# define BLUE_SKY 0x019CE0
# define EARTH_COLOR 0xB07C57
# define RED 0xFF0000
# define LIGHT_RED 0xFF4F4B
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define GOLDEN 0xFFDF00
# define CREAM 0xFFFDD0
# define BLUE 0x4278F5

# define S_WIDTH 880
# define S_HEIGHT 620
# define WALL_WIDTH 1
# define MINIMAP 0.05
# define FRAMES 7

# define TILE 256
# define PI 3.14159265358979323846
# define TWO_PI 6.28318530718
# define FOV 60

/*_______________IMAGES_STRUCT_________________*/
typedef struct s_image
{
	int				bpp;
	int				size_line;
	int				endian;
	char			*addrs;
	void			*img;
}					t_image;

/*_______________DOORS_STRUCT_________________*/
typedef struct s_door
{
	int				x;
	int				y;
	bool			open;
}					t_door;

typedef struct s_texture
{
	int				bpp;
	int				size_line;
	int				endian;
	char			*addrs;
	void			*img;
	int				tex_width;
	int				tex_height;
	void			*tex_data;
	char			*path;
}					t_texture;

typedef struct s_minimap
{
	int				start_x;
	int				start_y;
	double			dx;
	double			dy;
	double			steps;
	double			xinc;
	double			yinc;
	double			ray_angle;
	double			minimap_size;
	int				center_x;
	int				center_y;
	double			ray_length;
	int				visible_range;
	int				player_map_x;
	int				player_map_y;
	int				tile_x;
	int				tile_y;
}					t_minimap;

/*_______________PLAYER_STRCUT_________________*/
typedef struct s_player
{
	double			x;
	double			y;
	int				radius;
	double			turn_dir;
	double			walk_dir;
	double			side_dir;
	double			rotation_angle;
	double			rotation_speed;
	double			move_speed;
	double			fov;
	char			character;
	int				jab;
	int				frames;
}					t_player;

/*________________RAY_STRUCT_________________*/
typedef struct s_ray
{
	// used double data type for NOW, u can change it later;
	double			h_hitx;
	double			h_hity;
	double			v_hitx;
	double			v_hity;
	double			distance;
	bool			ray_down;
	bool			ray_up;
	bool			ray_right;
	bool			ray_left;
	bool			found_h_wall;
	bool			found_v_wall;
	bool			is_vert;
	double			x_wall;
	double			y_wall;
}					t_ray;

/*_______________
_GAME_STRUCT________________*/
typedef struct s_game
{
	void			*mlx;
	void			*win;

	char			**map;
	int				floor_color;
	int				ceiling_color;
	int				config_count;

	char			*no_texture;
	char			*we_texture;
	char			*so_texture;
	char			*ea_texture;

	int				map_height;
	int				map_width;

	double			num_rays;

	void			*wall_tex;
	int				tex_width;
	int				tex_height;
	unsigned int	*tex_data;

	double			corrected_wall;
	double			distance_projectplan;
	double			wall_projected_height;

	unsigned int	color;

	// you were going to add the number of rays the player will have
	t_player		*player;
	t_ray			*ray;
	t_image			*img;
	t_texture		*texture[4];
	char			*line;
	t_texture		*gun;
	t_minimap		*minimap;
}					t_game;

/*_____________new_functions______________*/

void				draw_map(t_game *data);
int					player_control(int key, t_game *data);
void				update_player(t_game *data, t_player *player);

/*_____________functions_functions______________*/

void				draw_rays(t_player *player, t_game *data);
double				normalize_angle(double angle);
void				cast_rays(t_player *player, t_game *data, double angle);
int					key_release(int key, t_game *data);

void				my_mlx_pixel_put(t_game *data, int x, int y, int color);

int					is_it_wall(t_game *data, double x, double y);
void				define_angle(t_ray *ray, double angle);

void				update_sides(t_game *data, t_player *player);
void				get_data(t_game *data);
int					game_loop(t_game *data);

void				escape_free(t_game *data);
void				destroy_sprite(t_game *data);
void				destroy_path(t_game *data);
void				wall_tex_free(t_game *data);
void				free_parse(t_game *game);

int					click_release(int key, int x, int y, t_game *data);
int					click_press(int key, int x, int y, t_game *data);

/*__________RAYCASTING_________*/
void				horizontal_intercepts(t_game *data, t_player *player,
						t_ray *ray, double angle);
void				horizontal_steps(double x_next_touch, double y_next_touch,
						t_game *data, double angle);
void				vertical_intercepts(t_game *data, t_player *player,
						t_ray *ray, double angle);
void				vertical_steps(double x_next_touch, double y_next_touch,
						t_game *data, double angle);
void				get_vertical_hit(t_game *data, double array[4], t_ray *ray);
void				get_horizontal_hit(t_game *data, double array[4],
						t_ray *ray);
void				closer_intersection(t_player *player, t_ray *ray);
double				cal_llen(double x1, double y1, double x2,
						double y2);

t_texture			*upload_texture(t_game *data, int i);

void				destroy_xpm(t_game *data);
void				draw_minimap(t_game *data);

void				inits(t_game *game, char **av);
void				init_mlx(t_game *game);
void				init_ray(t_game *data);
void				init_player(t_game *data);
void				get_texture(t_game *data, int j);
void				get_textures(t_game *data);
void				set_direction(t_game *data);
int					get_plyr_pos(t_game *data);

void				render_image(t_game *data, int wallTopPixel,
						int wallBottomPixel, int i);
void				put_ceiling(t_game *data, int walltop, int i);
void				put_wall(t_game *data, int wall_top, int wall_bottom,
						int i);
void				put_floor(t_game *data, int wall_bottom, int i);

/*______BRAHIM___________*/
void				error_msg(char *str);
void				parse_config(t_game *game, char **av);
void				read_map(t_game *game, char *file);
void				draw_map(t_game *game);
void				check_extension(const char *file, t_game *game);
void				count_params(t_game *game);
void				check_config(t_game *game);
void				check_map_params(t_game *game);
void				check_map_boundaries(t_game *game);
void				check_first_line(t_game *game, int *j);
void				check_last_line(t_game *game, int *j, int *i);
void				check_middle_line(t_game *game, int *i, int *j);
void				check_map_columns(t_game *game);
void				check_column_boundaries(t_game *game, int j);
void				check_column_zeros(t_game *game, int j, int i);
void				free_all(t_game *game);
void				calculate_map_dimensions(t_game *game, const char *file);
void				fill_map(t_game *game, const char *file);
char				*skip_empty_lines(int fd, t_game *game);
char				*parse_textures_and_colors(t_game *game, char *line,
						int fd);
char				*skip_texture_colors(int fd, char *line);
void				parse_texture(char *line, t_game *game, int n);
int					parse_color(char *str, t_game *game);
int					count_sep(char *str);
int					open_file(const char *file);
void				free_texture(t_game *game);
void				ft_free_split(char **array);
size_t				ft_arraylen(char **array);
int					ft_isspace(char *str);
int					validate_color_parts_count(char **parts, t_game *game);
int					validate_and_parse_color_values(char **parts, int *colors,
						t_game *game);
int					validate_color_format(char *str, t_game *game);
void				check_texture_validtion(t_game *game);
void				first_free(t_game *game, char *str);
void				second_free(t_game *game, char *str);
void				third_free(t_game *game, char *str);
char				*parse_color_line(t_game *game);
int					ft_isalldigit(const char *str);
void				free_func(t_game *game, char *trimmed_line);
char				*free_get(char *line, int fd);

#endif