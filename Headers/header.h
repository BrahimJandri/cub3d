/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:46:48 by bjandri           #+#    #+#             */
/*   Updated: 2024/12/18 10:44:20 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
#define HEADER_H

#include "../minilibx/mlx.h"
#include "../library/Libft/libft.h"
#include <get_next_line.h>
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
    size_t map_width;
    size_t map_height;
    int map_start;
} t_game;



#endif