/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:02:55 by bjandri           #+#    #+#             */
/*   Updated: 2024/10/10 11:03:34 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_read_map(t_game *game, char *argv)
{
	int		fd;
	char	*temp;
	int		len;

	fd = open(argv, O_RDONLY);
	error_open(fd);
	game->map_x = contline(fd);
	if (!game->map_x || game->map_x < 3)
		error_msg("Erorr\nInvalid map");
	close(fd);
	fd = open(argv, O_RDONLY);
	error_open(fd);
	temp = get_next_line(fd);
	if (temp[0] == '\n')
		error_msg("Erorr\nInvalid map");
	len = ft_strlen(temp) - 1;
	game->map_y = len;
	close(fd);
	fd = open(argv, O_RDONLY);
	error_open(fd);
	ft_fill_map(game, fd);
	close(fd);
	free(temp);
}
