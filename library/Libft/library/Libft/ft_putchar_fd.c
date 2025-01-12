/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reddamss <damssi.art@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:05:03 by reddamss          #+#    #+#             */
/*   Updated: 2023/11/30 10:20:30 by reddamss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = dst;
	s = src;
	if (dst == src)
		return (dst);
	while (n--)
		*d++ = *s++;
	return (dst);
}
