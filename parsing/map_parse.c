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
	ft_check_rows_map(game);
	ft_check_columns_map(game);
	ft_check_params(game);
}

void ft_check_rows_map(t_game *game)
{
    int i;
    char *trimmed_line;

    i = 0;
    while (i < game->map_y)
    {
        trimmed_line = ft_strtrim(game->map[i], " \t\n");
        if (ft_strlen(trimmed_line) == 0)
		{
            i++;
            continue;
        }
        if (trimmed_line[0] != '1' || trimmed_line[ft_strlen(trimmed_line) - 1] != '1')
            error_map("Error\nMap is not closed: missing walls in rows", game);
        i++;
    }
}



void ft_check_columns_map(t_game *game)
{
    int i;
    char *trimmed_first_line;
    char *trimmed_last_line;

    i = 0;
    while (i < game->map_y)
    {
        trimmed_first_line = ft_strtrim(game->map[i], " \t\n");
        trimmed_last_line = ft_strtrim(game->map[game->map_y - i - 1], " \t\n");
        if (ft_strlen(trimmed_first_line) > 0 && trimmed_first_line[0] != '1')
            error_map("Error\nMap is not closed: missing walls in first column", game);
        if (ft_strlen(trimmed_last_line) > 0 && trimmed_last_line[ft_strlen(trimmed_last_line) - 1] != '1')
            error_map("Error\nMap is not closed: missing walls in last column", game);
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
			else if (game->map[i][j] != '1' && game->map[i][j] != '0' && game->map[i][j] == 'N' && game->map[i][j] == 'S' && game->map[i][j] == 'E' && game->map[i][j] == 'W')
				error_map("Error\nInvalid params of the map", game);
			j++;
		}
		i++;
	}
}
