/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reddamss <damssi.art@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:53:03 by reddamss          #+#    #+#             */
/*   Updated: 2023/11/29 15:49:29 by reddamss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*string;
	int		length;

	string = (char *)s;
	length = ft_strlen(string);
	string += length;
	while (length--)
	{
		if (*string == (unsigned char)c)
			return (string);
		string--;
	}
	if (*string == (unsigned char)c)
		return (string);
	return (0);
}
