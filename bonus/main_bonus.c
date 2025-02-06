/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:09:58 by reddamss          #+#    #+#             */
/*   Updated: 2025/02/06 09:18:01 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Headers/cub3d_bonus.h"

int     close_window(t_game *data)
{
    free(data->ray);
    destroy_xpm(data);
    mlx_destroy_window(data->mlx, data->win);
    mlx_destroy_display(data->mlx);
    free(data->mlx);
    free(data->player);
    free(data->img);
    free_all(data);
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
    load_gun_frames(game);
    mlx_loop_hook(game->mlx, (void *)game_loop, game);
    mlx_hook(game->win, 2, (1L<<0), player_control, game);
    mlx_hook(game->win, 3, (1L<<1), key_release, game);
    mlx_hook(game->win, 17, 0, close_window, game);
    mlx_hook(game->win, 4, (1L<<2), click_press, game);
    mlx_hook(game->win, 5, (1L<<3), click_release, game);
    mlx_loop(game->mlx);
}
