/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:09:58 by reddamss          #+#    #+#             */
/*   Updated: 2025/02/08 12:58:01 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Headers/cub3d.h"

int     close_window(t_game *data)
{
    escape_free(data);
    free_all(data);
    write(1,"Exited\n",7);
    exit(0);
}


int main(int ac, char **av)
{
  	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
    if(!game)
    {
        return 1;
    }
	if(ac != 2)
    	return (ft_putstr_fd("Error\nUsage : Cub3d map.cub\n", 2), free(game),1);
    inits(game, av);
    game->img = malloc(sizeof(t_image));
    if(!game->img)
        return 1;
    mlx_loop_hook(game->mlx, game_loop, game);
    mlx_hook(game->win, 2, (1L<<0), player_control, game);
    mlx_hook(game->win, 3, (1L<<1), key_release, game);
    mlx_hook(game->win, 17, 0, close_window, game);
    mlx_loop(game->mlx);
}
