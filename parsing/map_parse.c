/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:57:51 by bjandri           #+#    #+#             */
/*   Updated: 2024/10/10 17:42:42 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int check_path(char *str)
{
    int len;
    int i;

    len = ft_strlen(str);
    i = len - 4;
    if (str[i] == '.' && str[i + 1] == 'c' && str[i + 2] == 'u' && str[i + 3] == 'b')
        return (1);
    return (0);
}

void	error_map(char *msg, t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i])
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

void	ft_check_all_map(t_game *game)
{
	ft_check_border_map(game);
	ft_check_params(game);
}

void	ft_check_border_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = game->map_y - 1;
	while (i < game->map_x)
	{
		if (game->map[i][0] != '1' || game->map[i][j] != '1')
			error_map("Error\nMap is not closed missing walls rows", game);
		i++;
	}
	i = 0;
	j = game->map_x - 1;
	while (i < game->map_y)
	{
		if (game->map[0][i] != '1' || game->map[j][i] != '1')
			error_map("Error\nMap is not closed missing walls columns", game);
		i++;
	}
}

void	ft_check_params(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_x)
	{
		j = 0;
		while (j < game->map_y)
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S' || game->map[i][j] == 'E' || game->map[i][j] == 'W')
			{
				game->player_x = i;
				game->player_y = j;
			}
			else if (game->map[i][j] != '1' && game->map[i][j] != 'N'
				&& game->map[i][j] != 'E' && game->map[i][j] != '0'
				&& game->map[i][j] != 'S' && game->map[i][j] != 'W')
				error_map("Error\nInvalid params of the map", game);
			j++;
		}
		i++;
	}
}
