/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reddamss <damssi.art@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 01:21:29 by reddamss          #+#    #+#             */
/*   Updated: 2023/11/29 18:14:02 by reddamss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	length;
	char	*p;

	length = 0;
	if (!s)
		return (0);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	else if (ft_strlen(s) - start < len)
		return (ft_strdup(&s[start]));
	while (length < len)
		length++;
	p = (char *)malloc((sizeof(char) * length) + 1);
	if (!p)
		return (0);
	length = 0;
	while (len--)
		p[length++] = s[start++];
	p[length] = '\0';
	return (p);
}
