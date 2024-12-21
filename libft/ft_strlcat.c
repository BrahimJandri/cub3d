/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reddamss <damssi.art@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:48:04 by reddamss          #+#    #+#             */
/*   Updated: 2023/11/28 0:15:01 by reddamss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	d;
	size_t	s;
	size_t	result;
	size_t	i;

	i = 0;
	d = 0;
	s = 0;
	if (dst == NULL && dstsize == 0)
		return (ft_strlen(src));
	while (dst[d] && d < dstsize)
		d++;
	while (src[s])
		s++;
	result = d + s;
	if (d == dstsize)
		return (result);
	while (src[i] && d < dstsize - 1)
	{
		dst[d] = src[i];
		d++;
		i++;
	}
	dst[d] = '\0';
	return (result);
}
