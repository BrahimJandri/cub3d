/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:10:58 by bjandri           #+#    #+#             */
/*   Updated: 2024/12/18 11:26:45 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Headers/cub3d.h"

void check_extension(const char *file_path)
{
	if (ft_strncmp(file_path + ft_strlen(file_path) - 4, ".cub", 4) != 0)
        error_msg("Error: Invalid file extension File must have a .cub extension.\n");
    else
        printf("Good Extension\n");
}

void parse_config(t_game *game, char **av)
{
    (void)game;
    check_extension(av[1]);
}