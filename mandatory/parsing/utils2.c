/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 21:48:29 by bjandri           #+#    #+#             */
/*   Updated: 2025/02/08 12:57:40 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

int	ft_isalldigit(const char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	free_func(t_game *game, char *trimmed_line)
{
	free(trimmed_line);
	third_free(game, "invalid color\n");
}

char	*free_get(char *line, int fd)
{
	free(line);
	line = get_next_line(fd);
	return (line);
}
