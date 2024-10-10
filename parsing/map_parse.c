/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:57:51 by bjandri           #+#    #+#             */
/*   Updated: 2024/10/10 11:03:09 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int check_path(char *str)
{
    int len;
    int i;

    len = ft_strlen(str);
    i = len - 4;
    if (str[i] == '.' && str[i + 1] == 'c' && str[i + 2] == 'u' && str[i + 3] == 'b')
        return (1);
    return (0);
}



int check_map(char **str)
{
    
}