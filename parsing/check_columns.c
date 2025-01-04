/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_columns.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 08:57:15 by bjandri           #+#    #+#             */
/*   Updated: 2024/12/29 11:28:29 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

void	check_left_boundary(t_game *game, int j)
{
	int	i;

	i = 0;
	while (game->map[i] && (j >= (int)ft_strlen(game->map[i])
			|| game->map[i][j] == ' ' || game->map[i][j] == '\t'
			|| game->map[i][j] == '\n' || game->map[i][j] == '\0'))
		i++;
	if (game->map[i] && j < (int)ft_strlen(game->map[i])
		&& game->map[i][j] != '1')
		error_msg("Error\nMap Not Surrounded by Walls");
}

void	check_right_boundary(t_game *game, int j)
{
	int	i;

	i = 0;
	while (game->map[i] && (j >= (int)ft_strlen(game->map[i])
			|| game->map[i][j] == ' ' || game->map[i][j] == '\t'
			|| game->map[i][j] == '\n' || game->map[i][j] == '\0'))
		i++;
	while (i > 0 && (j >= (int)ft_strlen(game->map[i - 1]) || game->map[i
				- 1][j] == ' ' || game->map[i - 1][j] == '\t' || game->map[i
			- 1][j] == '\n' || game->map[i - 1][j] == '\0'))
		i--;
	if (i > 0 && j < (int)ft_strlen(game->map[i - 1]) && game->map[i
			- 1][j] != '1')
		error_msg("Error\nMap Not Surrounded by Walls");
}

void	check_map_columns(t_game *game)
{
	int	j;
	int	i;

	j = 0;
	while (j < game->map_width)
	{
		check_left_boundary(game, j);
		i = 0;
		while (game->map[i] && j < (int)ft_strlen(game->map[i])
			&& game->map[i][j] != '\n')
			i++;
		check_right_boundary(game, j);
		j++;
	}
}
