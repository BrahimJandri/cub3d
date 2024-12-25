/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:45:30 by bjandri           #+#    #+#             */
/*   Updated: 2024/12/25 13:25:48 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

void	error_msg(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}

int	main(int ac, char **av)
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	if (ac != 2)
		return (ft_putstr_fd("Error\nUsage : Cub3d map.cub\n", 2),free(game), 1);
	parse_config(game, av);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->map_width * TILE_SIZE,
			game->map_height * TILE_SIZE, "Cub3D Map");
	draw_map(game);
	mlx_loop(game->mlx);
	free_all(game);
	return (0);
}
