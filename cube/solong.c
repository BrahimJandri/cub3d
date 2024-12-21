/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reddamss <reddamss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:09:20 by reddamss          #+#    #+#             */
/*   Updated: 2024/11/14 11:03:14 by reddamss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	read_map(char *av, t_game *data)
{
	int		fd;
	int		lines;
	char	*line;

	fd = open(av, O_RDONLY);
	line = get_next_line(fd);
	if (line == NULL)
		exit_mssg("Unvalid !");
	data->map_y = ft_strlen(line);
	free(line);
	close(fd);
	fd = open(av, O_RDONLY);
	lines = 0;
	line = get_next_line(fd);
	while (line)
	{
		lines++;
		free(line);
		line = get_next_line(fd);
	}
	data->map_x = lines;
	close(fd);
}

void	allocate_map(char *av, t_game *data)
{
	int		fd;
	int		i;
	char	*tmp;

	data->map = malloc(sizeof(char *) * (data->map_x + 1));
	if (!data->map)
		return ;
	fd = open(av, O_RDONLY);
	i = 0;
	tmp = get_next_line(fd);
	while (tmp)
	{
		data->map[i++] = ft_strdup(tmp);
		free(tmp);
		tmp = get_next_line(fd);
	}
	data->map[data->map_x] = NULL;
	close(fd);
}



void	draw_map(t_game *data)
{
	int	x;
	int	y;
	int color;

	x = 0;
	while (x < data->map_x)//is small than the height
	{
		y = 0;
		while (y < data->map_y - 1)//is small than the width
		{
			color = check_number(data->map[x][y]);
			build_square(data, y * TILE_SIZE, x * TILE_SIZE ,color);
			
			// printf("here [%d]\n", i);
			// mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr,
			// 	(y * 40), (x * 40));
			// mlx_destroy_image(data->mlx_ptr, data->img_ptr);
			y++;
		}
		x++;
	}
}