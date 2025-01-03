/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 08:54:39 by bjandri           #+#    #+#             */
/*   Updated: 2024/12/29 13:27:06 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

void check_texture_validtion(t_game *game)
{
	int fd;

	fd = open(game->no_texture, O_RDONLY);
	if(fd == -1)
	{
		error_msg("Error: Cannot open Texture\n");
	}
	fd = 0;
	fd = open(game->so_texture, O_RDONLY);
	if(fd == -1)
	{
		error_msg("Error: Cannot open Texture\n");
	}
	fd = 0;
	fd = open(game->ea_texture, O_RDONLY);
	if(fd == -1)
	{
		error_msg("Error: Cannot open Texture\n");
	}
	fd = 0;
	fd = open(game->we_texture, O_RDONLY);
	if(fd == -1)
	{
		error_msg("Error: Cannot open Texture\n");
	}
}

char	*parse_texture_line(t_game *game, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		parse_texture(line, game, 0);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		parse_texture(line, game, 1);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		parse_texture(line, game, 2);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		parse_texture(line, game, 3);
	else
		return (NULL);
	return (line);
}

char	*parse_color_line(t_game *game, char *line)
{
	if (ft_strncmp(line, "F ", 2) == 0)
		game->floor_color = parse_color(line + 2, game);
	else if (ft_strncmp(line, "C ", 2) == 0)
		game->ceiling_color = parse_color(line + 2, game);
	else
		return (NULL);
	return (line);
}

char	*parse_textures_and_colors(t_game *game, char *line, int fd)
{
	char	*trimmed_line;

	while (line)
	{
		trimmed_line = ft_strtrim(line, " \t");
		if (*trimmed_line == '\n')
		{
			free(line);
			free(trimmed_line);
			line = get_next_line(fd);
			continue ;
		}
		free(trimmed_line);
		if (parse_texture_line(game, line) == NULL)
		{
			if (parse_color_line(game, line) == NULL)
				break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

char	*skip_empty_lines(int fd)
{
	char	*line;
	char	*trimmed_line;

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
