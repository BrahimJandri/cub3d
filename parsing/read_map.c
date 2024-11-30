/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:02:55 by bjandri           #+#    #+#             */
/*   Updated: 2024/11/24 15:45:39 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

// int check_path(char *str)
// {
// 	int len;
// 	int i;

// 	len = ft_strlen(str);
// 	i = len - 4;
// 	if (str[i] == '.' && str[i + 1] == 'c' && str[i + 2] == 'u' && str[i + 3] == 'b')
// 		return (1);
// 	return (0);
// }

int ft_countlines(int fd)
{
	int i;
	char *line;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		i++;
		line = get_next_line(fd);
	}
	return (i);
}

void check_lines(char *line)
{
	char *line_trimed;
	int start;
	int end;

	start = 0;
	line_trimed = ft_strtrim(line, " \t\n");
	end = ft_strlen(line_trimed) - 1;
	printf("line start %c\n", line_trimed[start]);
	printf("line end %c\n", line_trimed[end]);
	if(line_trimed[start] != '1' || line_trimed[end] != '1')
	{
		printf("LINE_TRIMED = %s\n", line_trimed);
		printf("NOT CLOSE\n");
		exit(1);
	}
	else
		printf("Perfecto\n");
	free(line_trimed);
}

void error_open(int fd)
{
	if (fd == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
}

void read_map(t_game *game, char *file)
{
	(void)game;
	char *line;
	int fd;
	int linecount;

	fd = open(file, O_RDONLY);
	error_open(fd);
	linecount = ft_countlines(fd);
	if (!linecount)
	{
		perror("Error\nEmtpy Map");
		exit(EXIT_FAILURE);
	}
	close(fd);
	fd = open(file, O_RDONLY);
	error_open(fd);
	line = get_next_line(fd);
	while (line)
	{
		check_lines(line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}