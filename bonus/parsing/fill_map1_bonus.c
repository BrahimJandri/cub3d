/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map1_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 12:43:31 by bjandri           #+#    #+#             */
/*   Updated: 2025/02/06 21:46:46 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d_bonus.h"

void	calculate_map_dimensions(t_game *game, const char *file)
{
	int		fd;
	char	*trimed_line;
	int		line_length;

	fd = open_file(file);
	game->line = skip_empty_lines(fd, game);
	game->line = parse_textures_and_colors(game, game->line, fd);
	while (game->line)
	{
		trimed_line = ft_strtrim(game->line, "\n");
		game->map_height++;
		line_length = ft_strlen(trimed_line);
		if (line_length > game->map_width)
			game->map_width = line_length;
		free(game->line);
		free(trimed_line);
		game->line = get_next_line(fd);
	}
	close(fd);
}

char	*skip_empty_lines(int fd, t_game *game)
{
	char	*trimmed_line;

	game->line = get_next_line(fd);
	if (game->line == NULL)
		first_free(game, "Error\nEmpty file.\n");
	while (true)
	{
		if (game->line == NULL)
			return (NULL);
		trimmed_line = ft_strtrim(game->line, " \t");
		if (*trimmed_line == '\0')
		{
			free(trimmed_line);
			free(game->line);
			game->line = get_next_line(fd);
		}
		else
		{
			free(game->line);
			return (trimmed_line);
		}
	}
}

char	*read_and_process_line(int fd, t_game *game)
{
	char	*line;

	line = skip_empty_lines(fd, game);
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
	line = read_and_process_line(fd, game);
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
