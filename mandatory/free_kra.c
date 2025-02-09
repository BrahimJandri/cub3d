/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_kra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:06:54 by bjandri           #+#    #+#             */
/*   Updated: 2025/02/09 11:46:31 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Headers/cub3d.h"

void	destroy_xpm(t_game *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		mlx_destroy_image(data->mlx, data->texture[i]->img);
		i++;
	}
	i = 0;
	while (i < 4)
		free(data->texture[i++]);
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
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data->player);
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
}
