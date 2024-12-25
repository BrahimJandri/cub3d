/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_base5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 13:00:36 by bjandri           #+#    #+#             */
/*   Updated: 2024/12/25 11:22:21 by bjandri          ###   ########.fr       */
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

int ft_isspace(char *str)
{
	while (*str)
	{
		if (*str == ' ' || *str == '\t')
			return (0);
		str++;
	}
	return (1);
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
}

char *parse_texture(char *line, char **texture, t_game *game)
{
	char *trimmed_line;
	char **split_line;

	trimmed_line = ft_strtrim(line, " \t\n");
	split_line = ft_split(trimmed_line, ' ');
	if (split_line && ft_arraylen(split_line) >= 2)
	{
		*texture = ft_strdup(split_line[1]);
		game->config_count++;
	}
	else
		error_msg("Error\nInvalid texture line format.");
	ft_free_split(split_line);
	free(trimmed_line);
	return (*texture);
}

static void validate_color_format(char *str)
{
	char *trimmed_str;

	trimmed_str = ft_strtrim(str, " \t\n");
	if (!trimmed_str)
		error_msg("Error\nMemory allocation failed while trimming\n");
	if (count_sep(trimmed_str) != 2)
	{
		free(trimmed_str);
		error_msg("Error\nInvalid color format\n");
	}
	free(trimmed_str);
}

static char **split_and_trim_color_parts(char *str)
{
	char *trimmed_str;
	char **parts;

	trimmed_str = ft_strtrim(str, " \t\n");
	if (!trimmed_str)
		error_msg("Error\nMemory allocation failed while trimming\n");
	parts = ft_split(trimmed_str, ',');
	free(trimmed_str);
	if (!parts)
		error_msg("Error\nMemory allocation failed while splitting\n");
	return (parts);
}

static void validate_color_parts_count(char **parts)
{
	int count;

	count = 0;
	while (parts[count])
		count++;
	if (count != 3)
	{
		ft_free_split(parts);
		error_msg("Error\nInvalid color format\n");
	}
}

static void validate_and_parse_color_values(char **parts, int *colors)
{
	int i;

	i = 0;
	while (i < 3)
	{
		if (!ft_isspace(parts[i]))
		{
			ft_free_split(parts);
			error_msg("Error\nInvalid color format\n");
		}
		colors[i] = ft_atoi(parts[i]);
		if (colors[i] < 0 || colors[i] > 255)
		{
			ft_free_split(parts);
			error_msg("Error\nColor values must be in the range 0-255\n");
		}
		i++;
	}
}

static int convert_to_color(int *colors)
{
	return (colors[0] << 16) | (colors[1] << 8) | colors[2];
}

int parse_color(char *str, t_game *game)
{
	int colors[3];
	int color;
	char **parts;

	validate_color_format(str);
	parts = split_and_trim_color_parts(str);
	validate_color_parts_count(parts);
	validate_and_parse_color_values(parts, colors);
	ft_free_split(parts);
	color = convert_to_color(colors);
	game->config_count++;
	return (color);
}
