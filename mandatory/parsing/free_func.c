/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachid <rachid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 13:01:36 by bjandri           #+#    #+#             */
/*   Updated: 2025/01/27 16:41:09 by rachid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

int	open_file(const char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (error_msg("Error\nOpen file failed\n"), -1);
	return (fd);
}

void	free_texture(t_game *game)
{
	if (game->so_texture)
	{
		free(game->so_texture);
		game->so_texture = NULL;
	}
	if (game->no_texture)
	{
		free(game->no_texture);
		game->no_texture = NULL;
	}
	if (game->we_texture)
	{
		free(game->we_texture);
		game->we_texture = NULL;
	}
	if (game->ea_texture)
	{
		free(game->ea_texture);
		game->ea_texture = NULL;
	}
}

void	free_all(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i])
	{
		free(game->map[i]);
		i++;
	}
	i = 0;
	while (game->map_dup[i])
	{
		free(game->map_dup[i]);
		i++;
	}
	free(game->map);
	game->map = NULL;
	free(game->map_dup);
	game->map_dup = NULL;
	free_texture(game);
	free(game);
}

size_t	ft_arraylen(char **array)
{
	int	length;

	length = 0;
	while (array[length])
		length++;
	return (length);
}

void	ft_free_split(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void first_free(t_game *game, char *str)
{
    free(game->player);
    free(game);
    error_msg(str);
}

void third_free(t_game *game, char *str)
{
	free_texture(game);
	free(game->player);
	free(game->line);
	free(game);
	error_msg(str);
}

void second_free(t_game *game, char *str)
{
    int i;

    i = 0;
    free(game->player);
    while (game->map[i])
    {
        free(game->map[i]);
        i++;
    }
    free(game->map);
    free_texture(game);
    free(game);
    error_msg(str);
}