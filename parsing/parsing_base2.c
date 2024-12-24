/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_base2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 12:43:31 by bjandri           #+#    #+#             */
/*   Updated: 2024/12/24 13:08:24 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

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
		if (ft_strncmp(line, "NO ", 3) == 0)
			game->no_texture = parse_texture(line, &game->no_texture, game);
		else if (ft_strncmp(line, "SO ", 3) == 0)
			game->so_texture = parse_texture(line, &game->so_texture, game);
		else if (ft_strncmp(line, "WE ", 3) == 0)
			game->we_texture = parse_texture(line, &game->we_texture, game);
		else if (ft_strncmp(line, "EA ", 3) == 0)
			game->ea_texture = parse_texture(line, &game->ea_texture, game);
		else if (ft_strncmp(line, "F ", 2) == 0)
			game->floor_color = parse_color(line + 2, game);
		else if (ft_strncmp(line, "C ", 2) == 0)
			game->ceiling_color = parse_color(line + 2, game);
		else
			break;
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

char *skip_empty_lines(int fd)
{
	char *line = get_next_line(fd); // Get the first line from the file
	if (line == NULL)
	{
		error_msg("Error\nEmpty file.\n");
	}
	while (true)
	{
		if (line == NULL) // If there are no more lines (EOF)
			return (NULL);
		char *trimmed_line = ft_strtrim(line, " \t"); // Trim spaces and tabs
		if (*trimmed_line == '\0')
		// If the trimmed line is empty (just whitespace)
		{
			free(trimmed_line);		  // Free the trimmed line
			free(line);				  // Free the original line
			line = get_next_line(fd); // Get the next line
		}
		else
		{
			free(line); // Free the trimmed line
			return (trimmed_line);
			// Return the original line (without trimming)
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

void fill_map(t_game *game, const char *file)
{
	int fd;
	int i;
	int line_length;

	fd = open_file(file);
	i = 0;
	char *line = skip_empty_lines(fd); // Skip empty lines at the start
	line = skip_texture_colors(fd, line);
	game->map = malloc(sizeof(char *) * (game->map_height + 1));
	if (!game->map)
		error_msg("Error\nMemory allocation error");
	while (line)
	{
		if (*line != '\0')
		{
			line_length = ft_strlen(line);
			if (line_length < game->map_width)
			{
				// Allocate memory for a new padded line
				char *padded_line = malloc(game->map_width + 1);
				if (!padded_line)
					error_msg("Error\nMemory allocation error");
				ft_memcpy(padded_line, line, line_length);								  // Copy the existing line
				ft_memset(padded_line + line_length, ' ', game->map_width - line_length); // Pad with spaces
				padded_line[game->map_width] = '\0';									  // Null-terminate the line
				game->map[i] = padded_line;												  // Store the padded line
			}
			else
			{
				game->map[i] = ft_strdup(line); // Store the line as-is
			}
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	game->map[i] = NULL;
	close(fd);
}
