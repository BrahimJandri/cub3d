/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_base2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 12:43:31 by bjandri           #+#    #+#             */
/*   Updated: 2024/12/26 14:59:50 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

char *parse_texture_line(t_game *game, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		game->no_texture = parse_texture(line, &game->no_texture, game);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		game->so_texture = parse_texture(line, &game->so_texture, game);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		game->we_texture = parse_texture(line, &game->we_texture, game);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		game->ea_texture = parse_texture(line, &game->ea_texture, game);
	else
		return NULL;
	return line;
}

char *parse_color_line(t_game *game, char *line)
{
	if (ft_strncmp(line, "F ", 2) == 0)
		game->floor_color = parse_color(line + 2, game);
	else if (ft_strncmp(line, "C ", 2) == 0)
		game->ceiling_color = parse_color(line + 2, game);
	else
		return NULL;
	return line;
}

char *parse_textures_and_colors(t_game *game, char *line, int fd)
{
	char *trimmed_line;

	while (line)
	{
		trimmed_line = ft_strtrim(line, " \t");
		if (*trimmed_line == '\n')
		{
			free(line);
			free(trimmed_line);
			line = get_next_line(fd);
			continue;
		}
		free(trimmed_line);
		if (parse_texture_line(game, line) == NULL)
		{
			if (parse_color_line(game, line) == NULL)
				break;
		}
		free(line);
		line = get_next_line(fd);
	}
	return line;
}

char *skip_empty_lines(int fd)
{
	char *line;
	char *trimmed_line;

	line = get_next_line(fd);
	if (line == NULL)
	{
		error_msg("Error\nEmpty file.\n");
	}
	while (true)
	{
		if (line == NULL)
			return (NULL);
		trimmed_line = ft_strtrim(line, " \t");
		if (*trimmed_line == '\0')
		{
			free(trimmed_line);
			free(line);
			line = get_next_line(fd);
		}
		else
		{
			free(line);
			return (trimmed_line);
		}
	}
}

void calculate_map_dimensions(t_game *game, const char *file)
{
	int fd;
	char *line;
	char *trimed_line;
	int line_length;

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

char *read_and_process_line(int fd)
{
	char *line;

	line = skip_empty_lines(fd);
	return skip_texture_colors(fd, line);
}

char *pad_line(const char *line, int map_width)
{
	int line_length = ft_strlen(line);
	char *padded_line;

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
	return padded_line;
}

void fill_map(t_game *game, const char *file)
{
	int fd;
	int i = 0;
	char *line;

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
