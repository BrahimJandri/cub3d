/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_boundaries.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 08:58:21 by bjandri           #+#    #+#             */
/*   Updated: 2024/12/28 15:58:29 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

void	check_first_line(t_game *game, int *j)
{
	int	i;

	i = 0;
	while (game->map[i][*j] && game->map[i][*j] != '\n')
	{
		if (game->map[i][*j] != '1' && game->map[i][*j] != ' ' && game->map[i][*j] != '\t') 
			error_msg("Error\nMap Not Surrounded by Walls");
		(*j)++;
	}
}

void	check_last_line(t_game *game, int *j, int *i)
{
	while (game->map[*i][*j] && game->map[*i][*j] != '\n')
	{
		if (game->map[*i][*j] != '1' && game->map[*i][*j] != ' ')
			error_msg("Error\nMap Not Surrounded by Walls");
		(*j)++;
	}
}

void	check_middle_line(t_game *game, int *i, int *j)
{
	if (game->map[*i][*j] != '1' && game->map[*i][*j] != ' ')
		error_msg("Error\nMap Not Surrounded by Walls");
	while (game->map[*i][*j] && game->map[*i][*j] != '\n')
		(*j)++;
	if (game->map[*i][*j - 1] != '1' && game->map[*i][*j - 1] != ' ')
		error_msg("Error\nMap Not Surrounded by Walls");
}

void	check_map_boundaries(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j] && (game->map[i][j] == ' '
				|| game->map[i][j] == '\t'))
			j++;
		if (game->map[i][j] == '\0' || game->map[i][j] == '\n')
		{
			i++;
			continue ;
		}
		if (i == 0)
			check_first_line(game, &j);
		else if (game->map[i + 1] == NULL)
			check_last_line(game, &j, &i);
		else
			check_middle_line(game, &i, &j);
		i++;
	}
}
