/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_base5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 13:00:36 by bjandri           #+#    #+#             */
/*   Updated: 2024/12/24 13:01:14 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

int count_sep(char *str)
{
	int i;

	i = 0;
	while (*str)
	{
		if (*str == ',')
			i++;
		str++;
	}
	return (i);
}

int parse_color(char *str, t_game *game)
{
	char *trimmed_str;
	char **parts;
	int count;
	int colors[3];
	int i;
	int color;

	// Trim leading/trailing whitespace or newline characters
	trimmed_str = ft_strtrim(str, " \t\n");
	if (!trimmed_str)
		error_msg("Error\nMemory allocation failed while trimming\n");
	// Split the trimmed string by commas
	if (count_sep(trimmed_str) != 2)
	{
		error_msg("Error\nInvalid color format\n");
	}
	parts = ft_split(trimmed_str, ',');
	if (!parts)
	{
		free(trimmed_str);
		error_msg("Error\nMemory allocation failed while splitting\n");
	}
	// Check if the split resulted in exactly 3 parts (RGB)
	count = 0;
	while (parts[count])
		count++;
	if (count != 3)
	{
		ft_free_split(parts);
		free(trimmed_str);
		error_msg("Error\nInvalid color format\n");
	}
	// Parse and validate the RGB components
	i = 0;
	while (i < 3)
	{
		colors[i] = ft_atoi(parts[i]); // Convert string to integer
		// Check if the color value is in the range 0-255
		if (colors[i] < 0 || colors[i] > 255)
		{
			ft_free_split(parts);
			free(trimmed_str);
			error_msg("Error\nColor values must be in the range 0-255\n");
		}
		i++;
	}
	// Combine the RGB values into a single 24-bit color (8 bits per channel)
	color = (colors[0] << 16) | (colors[1] << 8) | colors[2];
	// Update the game's configuration count
	game->config_count++;
	// Clean up memory
	ft_free_split(parts);
	free(trimmed_str);
	return (color);
}

char *skip_texture_colors(int fd, char *line)
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
		if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 || ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
		{
			free(line);
			line = get_next_line(fd);
		}
		else if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ",
															  2) == 0)
		{
			free(line);
			line = get_next_line(fd);
		}
		else
			break;
	}
	return (line);
	// Return the line (could be NULL or valid line after processing)
}

// Function to skip empty lines and lines with only spaces/tabs/newlines

char *parse_texture(char *line, char **texture, t_game *game)
{
	char *trimmed_line;
	char **split_line;

	// Trim any leading/trailing whitespaces and newline characters
	trimmed_line = ft_strtrim(line, " \t\n");
	// Split the trimmed line by spaces
	split_line = ft_split(trimmed_line, ' ');
	if (split_line && ft_arraylen(split_line) >= 2)
	{
		*texture = ft_strdup(split_line[1]); // Store the texture path
		game->config_count++;
	}
	else
	{
		// Handle error if split fails or the format is incorrect
		error_msg("Error\nInvalid texture line format.");
	}
	// Free the split line array and the trimmed line
	ft_free_split(split_line);
	free(trimmed_line);
	return (*texture);
}