/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:46:48 by bjandri           #+#    #+#             */
/*   Updated: 2024/12/18 13:08:44 by bjandri          ###   ########.fr       */
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

typedef struct s_game
{
    char **map;
    char **map_dup;
    char *no_texture;
    char *we_texture;
    char *so_texture;
    char *ea_texture;
    int floor_color;
    int ceiling_color;
    int map_start;
    int line_number;
    size_t map_width;
    size_t map_height;
} t_game;

void error_msg(char *str);
void parse_config(t_game *game, char **av);
void read_map(t_game *game, char *file);

#endif