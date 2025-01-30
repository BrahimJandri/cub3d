/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachid <rachid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 12:45:08 by bjandri           #+#    #+#             */
/*   Updated: 2025/01/25 11:22:38 by rachid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

void count_params(t_game *game)
{
	int i;
	int j;
	int count;

	i = 0;
	count = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S' || game->map[i][j] == 'E' || game->map[i][j] == 'W')
			{
				game->player->y = i;
				game->player->x = j;
				count++;
			}
			j++;
		}
		i++;
	}
	if (count != 1)
	{
		free_error_texture(game);
		error_msg("Error\nInvalid params of the map");
	}
}

void check_map_params(t_game *game)
{
	int i;
	int j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (game->map[i][j])
		{
			if ((game->map[i][j] != '1' && game->map[i][j] != '0') && (game->map[i][j] != 'N' && game->map[i][j] != 'S' && game->map[i][j] != 'E' && game->map[i][j] != 'W') && game->map[i][j] != 32 && game->map[i][j] != '\n')
			{
				free_error_texture(game);
				error_msg("Error\nBad Params on map.");
			}
			j++;
		}
		i++;
	}
}

void check_config(t_game *game)
{
	if (game->config_count != 6)
	{
		free_error_texture(game);
		error_msg("Error\nTextures or Colors are not correct.");
	}
}
