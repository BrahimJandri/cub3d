/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reddamss <reddamss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:21:46 by reddamss          #+#    #+#             */
/*   Updated: 2024/11/06 13:00:55 by reddamss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

char	*get_strjoin(char *s1, char *s2)
{
	char	*p;
	int		len;
	int		i;

	i = 0;
	if (!s1)
		s1 = ft_strdup("");
	len = (ft_strlen(s1) + ft_strlen(s2));
	p = malloc((sizeof(char) * len) + 1);
	if (!p)
		return (NULL);
	len = 0;
	while (s1[len])
	{
		p[len] = s1[len];
		len++;
	}
	while (s2[i])
		p[len++] = s2[i++];
	p[len] = '\0';
	free(s1);
	return (p);
}




