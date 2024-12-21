/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reddamss <damssi.art@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 04:05:56 by reddamss          #+#    #+#             */
/*   Updated: 2023/11/30 10:28:25 by reddamss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;

	d = dst;
	s = (void *)src;
	if (dst == src)
		return (dst);
	if (d == s)
		return (d);
	if (d > s)
		while (len--)
			d[len] = s[len];
	else if (d < s)
		ft_memcpy(dst, src, len);
	return (d);
}
