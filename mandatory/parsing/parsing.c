/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 12:41:24 by bjandri           #+#    #+#             */
/*   Updated: 2025/02/06 21:48:04 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d_bonus.h"

void	read_map(t_game *game, char *file)
{
	calculate_map_dimensions(game, file);
	fill_map(game, file);
	count_params(game);
	check_config(game);
	check_texture_validtion(game);
	check_map_params(game);
	check_map_columns(game);
	check_map_boundaries(game);
}

void	init_game(t_game *game)
{
	game->map = NULL;
	game->no_texture = NULL;
	game->we_texture = NULL;
	game->so_texture = NULL;
	game->ea_texture = NULL;
	game->floor_color = -1;
	game->ceiling_color = -1;
	game->map_width = 0;
	game->map_height = 0;
	game->config_count = 0;
}

void	check_extension(const char *file, t_game *game)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		first_free(game, "Error\nOpen file failed\n");
	}
	if (ft_strncmp(file + ft_strlen(file) - 4, ".cub", 4) != 0)
	{
		first_free(game, "Error\nInvalid file extension\n");
	}
}

void	parse_config(t_game *game, char **av)
{
	check_extension(av[1], game);
	init_game(game);
	read_map(game, av[1]);
}
