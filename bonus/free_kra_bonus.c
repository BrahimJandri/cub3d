/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_kra_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:36:51 by bjandri           #+#    #+#             */
/*   Updated: 2025/02/08 19:17:54 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Headers/cub3d_bonus.h"

void	destroy_path(t_game *data)
{
	int	i;

	i = 0;
	while (i < FRAMES)
	{
		free(data->gun[i].path);
		i++;
	}
	return ;
}

void	destroy_sprite(t_game *data)
{
	int	i;

	i = 0;
	while (i < FRAMES)
	{
		mlx_destroy_image(data->mlx, data->gun[i].img);
		i++;
	}
	return ;
}

void	free_parse(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i])
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
	game->map = NULL;
	free_texture(game);
}

void	wall_tex_free(t_game *data)
{
	free(data->ray);
	destroy_path(data);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data->player);
	free(data->gun);
	free_parse(data);
	free(data);
}

void	escape_free(t_game *data)
{
	free(data->ray);
	destroy_xpm(data);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data->player);
	free(data->img);
	free(data->gun);
}
