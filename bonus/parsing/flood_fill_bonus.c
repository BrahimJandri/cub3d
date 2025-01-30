/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 12:52:43 by bjandri           #+#    #+#             */
/*   Updated: 2024/12/29 11:27:14 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d_bonus.h"

void	map_dup(t_game *game)
{
	int	i;

	i = 0;
	game->map_dup = malloc(sizeof(char *) * (game->map_height + 1));
	while (i < game->map_height)
	{
		game->map_dup[i] = ft_strdup(game->map[i]);
		i++;
	}
	game->map_dup[i] = NULL;
}

bool	ft_flood_fill(int x, int y, t_game *game)
{
	bool	up;
	bool	down;
	bool	left;
	bool	right;

	if (x < 0 || y < 0 || x >= game->map_height || y >= game->map_width)
		return (false);
	if (game->map_dup[x][y] == 'V' || game->map[x][y] == '1')
		return (true);
	if (game->map[x][y] == ' ')
		return (false);
	game->map_dup[x][y] = 'V';
	up = ft_flood_fill(x - 1, y, game);
	down = ft_flood_fill(x + 1, y, game);
	left = ft_flood_fill(x, y - 1, game);
	right = ft_flood_fill(x, y + 1, game);
	return (up && down && left && right);
}
