/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:46:48 by bjandri           #+#    #+#             */
/*   Updated: 2024/10/10 17:42:01 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "./minilibx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "Libft/libft.h"
# include <signal.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_game
{
    void    *mlx;
    void    *win;
    char    **map;
    int     player_x;
    int     player_y;
    int     map_x;
    int     map_y;
}               t_game;


int	    ft_strllen(char *str);
char	*ft_strjjoin(char *s1, char *s2);
char	*ft_free(char *str);
char	*ft_first_line(int fd, char *str);
char	*ft_next_line(char *str);
char	*ft_new_str(char *str);
char	*get_next_line(int fd);
int     check_path(char *str);
void	error_open(int fd);
int     read_map(t_game *game, char *argv);
void	ft_check_all_map(t_game *game);
void    ft_check_border_map(t_game *game);
void    ft_check_params(t_game *game);
void	error_map(char *msg, t_game *game);


#endif