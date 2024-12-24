/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_base4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 12:52:43 by bjandri           #+#    #+#             */
/*   Updated: 2024/12/24 12:53:24 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

void map_dup(t_game *game)
{
	int i;

	i = 0;
	game->map_dup = malloc(sizeof(char *) * (game->map_height + 1));
	while (i < game->map_height)
	{
		game->map_dup[i] = ft_strdup(game->map[i]);
		i++;
	}
	game->map_dup[i] = NULL;
}

bool ft_flood_fill(int x, int y, t_game *game)
{
	bool up, down, left, right;
	// Check if we are out of bounds
	if (x < 0 || y < 0 || x >= game->map_height || y >= game->map_width)
		return (false); // Found an edge without walls.
	// Check if the current cell is already visited or is a wall
	if (game->map_dup[x][y] == 'V' || game->map_dup[x][y] == '1')
		return (true);
	// Check if there is a '0' followed by a space in any direction
	if ((game->map[x][y] == '0' && (x > 0 && game->map[x - 1][y] == ' ')) ||					// Up
		(game->map[x][y] == '0' && (x < game->map_height - 1 && game->map[x + 1][y] == ' ')) || // Down
		(game->map[x][y] == '0' && (y > 0 && game->map[x][y - 1] == ' ')) ||					// Left
		(game->map[x][y] == '0' && (y < game->map_width - 1 && game->map[x][y + 1] == ' ')))	// Right
		return (false);
	// Mark the current cell as visited
	game->map_dup[x][y] = 'V';
	// Recursively check all directions
	up = ft_flood_fill(x - 1, y, game);
	down = ft_flood_fill(x + 1, y, game);
	left = ft_flood_fill(x, y - 1, game);
	right = ft_flood_fill(x, y + 1, game);
	// Return the result of all directions
	return (up && down && left && right);
}
