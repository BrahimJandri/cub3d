/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:10:58 by bjandri           #+#    #+#             */
/*   Updated: 2024/12/18 11:49:38 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Headers/cub3d.h"

void check_extension(const char *file)
{
    int fd;
    
    fd = open(file, O_RDONLY);
    if(fd == -1)
        error_msg("Error: File deosn't exicte or no permession\n");
    if (ft_strncmp(file + ft_strlen(file) - 4, ".cub", 4) != 0)
        error_msg("Error: Invalid file extension File must have a .cub extension.\n");
  
}

void init_game(t_game *game)
{
    game->map = NULL;
    game->map_dup = NULL;
    game->no_texture = NULL;
    game->we_texture = NULL;
    game->so_texture = NULL;
    game->ea_texture = NULL;
    game->floor_color = -1;
    game->ceiling_color = -1;
    game->line_number = 1;
    game->map_width = 0;
    game->map_height = 0;
}

void parse_config(t_game *game, char **av)
{
    check_extension(av[1]);
    init_game(game);
    read_map(game, av[1]);
}