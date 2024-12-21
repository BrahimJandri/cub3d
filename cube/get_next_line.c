/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reddamss <reddamss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:14:53 by reddamss          #+#    #+#             */
/*   Updated: 2024/11/07 11:12:12 by reddamss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

char	*remaining(char *blended)
{
	char	*remain;
	int		i;
	int		j;

	i = 0;
	if (!blended[i])
		return (free(blended), NULL);
	while (blended[i] && blended[i] != '\n')
		i++;
	if (!blended[i])
		return (free(blended), NULL);
	remain = malloc((ft_strlen(blended) - i + 1) * sizeof(char));
	if (!remain)
		return (NULL);
	i++;
	j = 0;
	while (blended[i])
		remain[j++] = blended[i++];
	remain[j] = '\0';
	free(blended);
	return (remain);
}

char	*extract(char *blended)
{
	char	*line;
	int		i;

	i = 0;
	if (!blended[i])
		return (NULL);
	while (blended[i] && blended[i] != '\n')
		i++;
	line = malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (blended[i] && blended[i] != '\n')
	{
		line[i] = blended[i];
		i++;
	}
	if (blended[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*fill(int fd, char *pail)
{
	char	*scoope;
	ssize_t	count;

	scoope = malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!scoope)
		return (NULL);
	count = 1;
	while (ft_strchr(pail, '\n') == NULL && count != 0)
	{
		count = read(fd, scoope, BUFFER_SIZE);
		if (count == -1)
		{
			free(pail);
			free(scoope);
			return (NULL);
		}
		scoope[count] = '\0';
		pail = get_strjoin(pail, scoope);
	}
	free(scoope);
	return (pail);
}

char	*get_next_line(int fd)
{
	static char	*pail;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	pail = fill(fd, pail);
	if (!pail)
		return (NULL);
	line = extract(pail);
	pail = remaining(pail);
	return (line);
}
