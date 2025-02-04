/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:59:57 by bjandri           #+#    #+#             */
/*   Updated: 2025/02/04 16:02:29 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

void	first_free(t_game *game, char *str)
{
	free(game->player);
	free(game);
	error_msg(str);
}

void	third_free(t_game *game, char *str)
{
	free_texture(game);
	free(game->player);
	free(game->line);
	free(game);
	error_msg(str);
}

void	second_free(t_game *game, char *str)
{
	int	i;

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
