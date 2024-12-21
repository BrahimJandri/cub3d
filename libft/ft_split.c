/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reddamss <damssi.art@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 10:01:06 by reddamss          #+#    #+#             */
/*   Updated: 2023/11/30 11:39:28 by reddamss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_in(char **res, int index, int length)
{
	int	i;

	i = 0;
	res[index] = malloc(sizeof(char) * (length + 1));
	if (!res[index])
	{
		while (i < index)
			free(res[i++]);
		free(res);
		return (1);
	}
	return (0);
}

static int	allocate(char **res, const char *s, char c)
{
	int	i;
	int	index;

	index = 0;
	while (*s)
	{
		i = 0;
		while (*s == c)
			s++;
		while (*s != c && *s)
		{
			i++;
			s++;
		}
		if (i)
		{
			if (check_in(res, index, i))
				return (1);
			ft_strlcpy(res[index++], s - i, i + 1);
		}
	}
	return (0);
}

static int	count_words(const char *str, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i])
			words++;
		while (str[i] != c && str[i])
			i++;
	}
	return (words);
}

char	**ft_split(const char *s, char c)
{
	int		words;
	char	**result;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	result = (char **)malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	result[words] = NULL;
	if (allocate(result, s, c))
		return (NULL);
	return (result);
}
