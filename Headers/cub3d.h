/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:46:48 by bjandri           #+#    #+#             */
/*   Updated: 2024/12/29 13:15:43 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "../library/minilibx/mlx.h"
#include "../library/Libft/libft.h"
#include "../library/get_next_line/get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>

#define TILE_SIZE 32

#define TEXWIDTH 64
#define TEXHEIGHT 64


typedef struct s_game
{
    void *win;
    void *mlx;
    char **map;
    char **map_dup;
    char *no_texture;
    char *we_texture;
    char *so_texture;
    char *ea_texture;
    int floor_color;
    int ceiling_color;
    int player_x;
    int player_y;
    int player_found;
    int config_count;
    int map_width;
    int map_height;
} t_game;

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
// char *trim_leading_whitespace(const char *line);

#endif