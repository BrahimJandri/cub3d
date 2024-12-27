/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_boundaries.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 08:58:21 by bjandri           #+#    #+#             */
/*   Updated: 2024/12/27 09:56:43 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

void	check_initial_final_lines(t_game *game, int i)
{
	int	j;

	j = 0;
	while (game->map[i][j] && game->map[i][j] != '\n')
	{
		if (game->map[i][j] != '1' && game->map[i][j] != ' '
			&& game->map[i][j] != '\t')
			error_msg("Error\nMap Not Surrounded by Walls");
		j++;
	}
}

void	check_middle_lines(t_game *game, int i)
{
	int	j;

	j = 0;
	while (game->map[i][j] && (game->map[i][j] == ' '
			|| game->map[i][j] == '\t'))
		j++;
	if (game->map[i][j] != '1')
		error_msg("Error\nMap Not Surrounded by Walls in Middle Line 1");
	while (game->map[i][j] && game->map[i][j] != '\n')
		j++;
	if (game->map[i][j - 1] != '1' && game->map[i][j - 1] != ' '
		&& game->map[i][j - 1] != '\t')
		error_msg("Error\nMap Not Surrounded by Walls in Middle Line 2");
}

void	check_map_boundaries(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i])
	{
		if (i == 0 || game->map[i + 1] == NULL)
			check_initial_final_lines(game, i);
		else
			check_middle_lines(game, i);
		i++;
	}
}
