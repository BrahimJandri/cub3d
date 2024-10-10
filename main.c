/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:13:19 by bjandri           #+#    #+#             */
/*   Updated: 2024/10/10 14:05:22 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minilibx/mlx.h"
#include "header.h"


int main(int ac, char **av)
{
    if(ac != 2)
    {
        printf("Error Extension of map\n");
        return (0);
    }
    else if(!check_path(av[1]))
    {
        printf("Error Extension of map\n");
        return (0);
    }
    else
        printf("Good Extension of map\n");
    
    return (0);
}