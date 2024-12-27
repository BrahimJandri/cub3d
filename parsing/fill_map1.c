/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 12:43:31 by bjandri           #+#    #+#             */
/*   Updated: 2024/12/27 08:55:13 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

void	calculate_map_dimensions(t_game *game, const char *file)
{
	int		fd;
	char	*line;
	char	*trimed_line;
	int		line_length;

	fd = open_file(file);
	line = skip_empty_lines(fd);
	line = parse_textures_and_colors(game, line, fd);
	while (line)
	{
		trimed_line = ft_strtrim(line, " \t\n");
		game->map_height++;
		line_length = ft_strlen(trimed_line);
		if (line_length > game->map_width)
			game->map_width = line_length;
		free(line);
		free(trimed_line);
		line = get_next_line(fd);
	}
	close(fd);
}

char	*read_and_process_line(int fd)
{
	char	*line;

	line = skip_empty_lines(fd);
	return (skip_texture_colors(fd, line));
}

char	*pad_line(const char *line, int map_width)
{
	int		line_length;
	char	*padded_line;

	line_length = ft_strlen(line);
	if (line_length < map_width)
	{
		padded_line = malloc(map_width + 1);
		if (!padded_line)
			error_msg("Error\nMemory allocation error");
		ft_memcpy(padded_line, line, line_length);
		ft_memset(padded_line + line_length, ' ', map_width - line_length);
		padded_line[map_width] = '\0';
	}
	else
	{
		padded_line = ft_strdup(line);
	}
	return (padded_line);
}

void	fill_map(t_game *game, const char *file)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open_file(file);
	line = read_and_process_line(fd);
	game->map = malloc(sizeof(char *) * (game->map_height + 1));
	if (!game->map)
		error_msg("Error\nMemory allocation error");
	while (line)
	{
		if (*line != '\0')
		{
			game->map[i] = pad_line(line, game->map_width);
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	game->map[i] = NULL;
	close(fd);
}
