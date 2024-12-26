/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_base3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 12:45:08 by bjandri           #+#    #+#             */
/*   Updated: 2024/12/26 15:07:43 by bjandri          ###   ########.fr       */
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
				game->player_x = i;
				game->player_y = j;
				count++;
			}
			j++;
		}
		i++;
	}
	if (count != 1)
		error_msg("Error\nInvalid params of the map");
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
				error_msg("Error\nBad Params on map.");
			j++;
		}
		i++;
	}
}

void check_config(t_game *game)
{
	if (game->config_count != 6)
		error_msg("Error\nTextures or Colors are not correct.");
}

void check_map_columns(t_game *game)
{
	int i;
	int j;

	j = 0;
	while (j < game->map_width)
	{
		i = 0;
		while (game->map[i] && (j >= (int)ft_strlen(game->map[i]) || game->map[i][j] == ' ' || game->map[i][j] == '\t' || game->map[i][j] == '\n' || game->map[i][j] == '\0'))
			i++;
		if (game->map[i] && j < (int)ft_strlen(game->map[i]) && game->map[i][j] != '1')
			error_msg("Error\nMap Not Surrounded by Walls at Left Boundary");
		while (game->map[i] && j < (int)ft_strlen(game->map[i]) && game->map[i][j] != '\n')
			i++;
		while (i > 0 && (j >= (int)ft_strlen(game->map[i - 1]) || game->map[i - 1][j] == ' ' || game->map[i - 1][j] == '\t' || game->map[i - 1][j] == '\n' || game->map[i - 1][j] == '\0'))
			i--;
		if (i > 0 && j < (int)ft_strlen(game->map[i - 1]) && game->map[i - 1][j] != '1')
			error_msg("Error\nMap Not Surrounded by Walls at Right Boundary");
		j++;
	}
}

void check_map_boundaries(t_game *game)
{
	int i;
	int j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j] && (game->map[i][j] == ' ' || game->map[i][j] == '\t'))
			j++;
		if (game->map[i][j] == '\0' || game->map[i][j] == '\n')
		{
			i++;
			continue;
		}
		if (i == 0)
		{
			while (game->map[i][j] && game->map[i][j] != '\n')
			{
				if (game->map[i][j] != '1' && game->map[i][j] != ' ' && game->map[i][j] != '\t')
					error_msg("Error\nMap Not Surrounded by Walls");
				j++;
			}
		}
		else if (game->map[i + 1] == NULL)
		{
			while (game->map[i][j] && game->map[i][j] != '\n')
			{
				if (game->map[i][j] != '1' && game->map[i][j] != ' ')
					error_msg("Error\nMap Not Surrounded by Walls");
				j++;
			}
		}
		else
		{
			if (game->map[i][j] != '1')
				error_msg("Error\nMap Not Surrounded by Walls in Middle Line 1");
			while (game->map[i][j] && game->map[i][j] != '\n')
				j++;
			if (game->map[i][j - 1] != '1' && game->map[i][j - 1] != ' ' && game->map[i][j - 1] != '\t')
				error_msg("Error\nMap Not Surrounded by Walls in Middle Line 2");
		}
		i++;
	}
}
