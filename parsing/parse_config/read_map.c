/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:45:30 by bjandri           #+#    #+#             */
/*   Updated: 2024/12/18 11:59:46 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Headers/cub3d.h"

int open_file(const char *file)
{
    int fd;

    fd = open(file, O_RDONLY);
    if(fd == -1)
        return(error_msg("Error: Open file fail\n"), 1);
    
}

void read_map(t_game *game, char *file)
{
    int fd;
    char *line;

    
    fd = open(file, O_RDONLY);
    if(fd == -1)
        error_msg("Error: open file Fail\n");
    
}