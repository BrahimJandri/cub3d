/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<<< HEAD:library/Libft/ft_strcpy.c
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 00:58:00 by reddamss          #+#    #+#             */
/*   Updated: 2024/12/22 09:04:10 by bjandri          ###   ########.fr       */
========
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reddamss <damssi.art@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 01:59:19 by reddamss          #+#    #+#             */
/*   Updated: 2023/11/29 18:21:02 by reddamss         ###   ########.fr       */
>>>>>>>> Damssi:library/Libft/library/Libft/ft_strjoin.c
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

<<<<<<<< HEAD:library/Libft/ft_strcpy.c
char	*ft_strcpy(char *s1, char *s2)
========
char	*ft_strjoin(const char *s1, const char *s2)
>>>>>>>> Damssi:library/Libft/library/Libft/ft_strjoin.c
{
	int	i;

	i = 0;
<<<<<<<< HEAD:library/Libft/ft_strcpy.c
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = s2[i];
	return (s1);
}
========
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
>>>>>>>> Damssi:library/Libft/library/Libft/ft_strjoin.c
