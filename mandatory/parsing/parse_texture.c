/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachid <rachid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 08:54:39 by bjandri           #+#    #+#             */
/*   Updated: 2025/01/25 13:11:00 by rachid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

void	check_texture_validtion(t_game *game)
{
	int	fd;

	fd = open(game->no_texture, O_RDONLY);
	if (fd == -1)
	{
		error_msg("Error: Cannot open Texture\n");
	}
	fd = 0;
	fd = open(game->so_texture, O_RDONLY);
	if (fd == -1)
	{
		error_msg("Error: Cannot open Texture\n");
	}
	fd = 0;
	fd = open(game->ea_texture, O_RDONLY);
	if (fd == -1)
	{
		error_msg("Error: Cannot open Texture\n");
	}
	fd = 0;
	fd = open(game->we_texture, O_RDONLY);
	if (fd == -1)
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

void	parse_texture(char *line, t_game *game, int n)
{
	char	*trimmed_line;
	char	**split_line;

	trimmed_line = ft_strtrim(line, " \t\n");
	split_line = ft_split(trimmed_line, ' ');
	if (split_line && ft_arraylen(split_line) >= 2)
	{
		if (n == 0 && game->config_count < 6)
			game->no_texture = ft_strdup(split_line[1]);
		else if (n == 1 && game->config_count < 6)
			game->so_texture = ft_strdup(split_line[1]);
		else if (n == 2 && game->config_count < 6)
			game->we_texture = ft_strdup(split_line[1]);
		else if (n == 3 && game->config_count < 6)
			game->ea_texture = ft_strdup(split_line[1]);
		game->config_count++;
	}
	else
		error_msg("Error\nInvalid texture line format.");
	ft_free_split(split_line);
	free(trimmed_line);
}
