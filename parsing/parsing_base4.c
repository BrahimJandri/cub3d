/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_base4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 12:52:43 by bjandri           #+#    #+#             */
/*   Updated: 2024/12/24 13:24:14 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

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
	bool up, down, left, right;
	if (x < 0 || y < 0 || x >= game->map_height || y >= game->map_width)
		return (false);
	if (game->map_dup[x][y] == 'V' || game->map_dup[x][y] == '1')
		return (true);
	if ((game->map[x][y] == '0' && (x > 0 && game->map[x - 1][y] == ' '))
		|| (game->map[x][y] == '0' && (x < game->map_height - 1 && game->map[x
				+ 1][y] == ' ')) || (game->map[x][y] == '0' && (y > 0
				&& game->map[x][y - 1] == ' ')) || (game->map[x][y] == '0'
			&& (y < game->map_width - 1 && game->map[x][y + 1] == ' ')))
		return (false);
	game->map_dup[x][y] = 'V';
	up = ft_flood_fill(x - 1, y, game);
	down = ft_flood_fill(x + 1, y, game);
	left = ft_flood_fill(x, y - 1, game);
	right = ft_flood_fill(x, y + 1, game);
	return (up && down && left && right);
}
