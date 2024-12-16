/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reddamss <damssi.art@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 01:59:19 by reddamss          #+#    #+#             */
/*   Updated: 2023/11/29 18:21:02 by reddamss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*p;
	int		len;
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	len = (ft_strlen((char *)s1) + ft_strlen((char *)s2));
	p = (char *)malloc((sizeof(char) * len) + 1);
	if (!p)
		return (0);
	len = 0;
	while (s1[len])
	{
		p[len] = s1[len];
		len++;
	}
	while (s2[i])
		p[len++] = s2[i++];
	p[len] = '\0';
	return (p);
}
