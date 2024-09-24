/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:13:19 by bjandri           #+#    #+#             */
/*   Updated: 2024/09/24 20:46:26 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minilibx-linux/mlx.h"
#include <stdio.h>


int main(int ac, char **av)
{
    if(ac != 2)
    {
        printf("Error\n");
        return (0);
    }
    else if(!check_path(av[1]))
    {
        printf("Error\n");
        return (0);
    }
    
    return (0);
}