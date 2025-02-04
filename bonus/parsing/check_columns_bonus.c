/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_columns_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 08:57:15 by bjandri           #+#    #+#             */
/*   Updated: 2025/02/04 16:36:58 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d_bonus.h"

void	check_map_columns(t_game *game)
{
	int	i;
	int	j;

	j = 0;
	while (j < game->map_width)
	{
		i = 0;
		while (game->map[i] && (j >= (int)ft_strlen(game->map[i])
				|| game->map[i][j] == ' ' || game->map[i][j] == '\t'
				|| game->map[i][j] == '\n' || game->map[i][j] == '\0'))
			i++;
		check_column_boundaries(game, j);
		check_column_zeros(game, j, i);
		j++;
	}
}

void	check_column_boundaries(t_game *game, int j)
{
	int	i;

	i = 0;
	while (game->map[i] && (j >= (int)ft_strlen(game->map[i])
			|| game->map[i][j] == ' ' || game->map[i][j] == '\t'
			|| game->map[i][j] == '\n' || game->map[i][j] == '\0'))
		i++;
	if (game->map[i] && j < (int)ft_strlen(game->map[i])
		&& game->map[i][j] != '1')
		second_free(game, "Error\nMap Not Surrounded by Walls");
	while (game->map[i] && j < (int)ft_strlen(game->map[i])
		&& game->map[i][j] != '\n')
		i++;
	while (i > 0 && (j >= (int)ft_strlen(game->map[i - 1]) || game->map[i
				- 1][j] == ' ' || game->map[i - 1][j] == '\t' || game->map[i
			- 1][j] == '\n' || game->map[i - 1][j] == '\0'))
		i--;
	if (i > 0 && j < (int)ft_strlen(game->map[i - 1]) && game->map[i
			- 1][j] != '1')
		second_free(game, "Error\nMap Not Surrounded by Walls");
}

void	check_column_zeros(t_game *game, int j, int i)
{
	while (game->map[i] && j < (int)ft_strlen(game->map[i])
		&& game->map[i][j] != '\n')
	{
		if (game->map[i][j] == '0')
		{
			if ((i == 0 || j == 0 || i >= game->map_height - 1
					|| j >= (int)ft_strlen(game->map[i]) - 1) || game->map[i
					- 1][j] == ' ' || game->map[i + 1][j] == ' '
					|| game->map[i][j
				- 1] == ' ' || game->map[i][j + 1] == ' ')
				second_free(game, "Error\nMap Not Surrounded by Walls");
		}
		i++;
	}
}
