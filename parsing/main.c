/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:13:19 by bjandri           #+#    #+#             */
/*   Updated: 2024/12/18 11:28:03 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

int	main(int ac, char **av)
{
	t_game	*game;
	
	game = (t_game *)malloc(sizeof(t_game));
	if(ac != 2)
		return(ft_putstr_fd("Error\nUsage : Cub3d map.cub", 2), 1);
	parse_config(game, av);
	free(game);
	return (0);
}
