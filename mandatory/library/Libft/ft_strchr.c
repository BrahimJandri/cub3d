/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reddamss <reddamss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:58:44 by reddamss          #+#    #+#             */
/*   Updated: 2024/11/07 11:07:19 by reddamss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*string;

	string = (char *)s;
	if(!string)
		return NULL;
	while (*string)
	{
		if ((char)c == *string)
			return (string);
		string++;
	}
	if ((char)c == '\0')
		return (string);
	return NULL;
}
