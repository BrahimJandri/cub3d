/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:13:19 by bjandri           #+#    #+#             */
/*   Updated: 2024/11/24 14:59:54 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// int check_extension(int ac, char **av)
// {
//     if(ac != 2)
//         return (1);
//     else if(!check_path(av[1]))
//         return (1);
//     else
//         return (0);
// }

int main(int ac, char **av)
{
    t_game game;
    (void)ac;
    // if(check_extension(ac, av))
    //     return(perror("Error\nBad Extension"), 1);
    ft_memset(&game, 0, sizeof(t_game));
    read_map(&game, av[1]);
    free_all(&game);
    return (0);
}