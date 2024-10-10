/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:02:55 by bjandri           #+#    #+#             */
/*   Updated: 2024/10/10 12:35:53 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	error_open(int fd)
{
	if (fd == -1)
	{
		error_msg("Error opening file");
		exit(EXIT_FAILURE);
	}
}

int read_map(char *argv)
{
    int fd;

    fd = open(argv, O_RDONLY);
    error_open(fd);
    
}
