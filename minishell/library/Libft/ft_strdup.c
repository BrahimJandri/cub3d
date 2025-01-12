/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reddamss <damssi.art@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 23:25:27 by reddamss          #+#    #+#             */
/*   Updated: 2023/11/17 03:39:09 by reddamss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*p;

	len = ft_strlen((char *)s1);
	p = malloc((len * sizeof(char)) + 1);
	if (!p)
		return (0);
	len = 0;
	while (s1[len])
	{
		p[len] = s1[len];
		len++;
	}
	p[len] = '\0';
	return (p);
}
